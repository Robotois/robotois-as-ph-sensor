const Sensor = require('bindings')('PhSensor');

const round = (value, decimals) => {
  return Number(Math.round(value+'e'+decimals)+'e-'+decimals);
}

/**
 * Creates an instance of PhSensor.
 * @param {int} add The second argument.
 * @returns {PhSensor}.
 */
function PhSensor({ client, topic }, addr = 0) {
  const self = this;
  // EventEmitter.call(this);
  this.ph = new Sensor(addr);
  this.prevValue = -1;
  this.client = client;
  this.topic = topic;
  this.eventInterval = false;

  process.on('SIGINT', () => {
    self.disableMonitor();
  });

  process.on('SIGTERM', () => {
    self.disableMonitor();
  });
}

PhSensor.prototype.initClient = function initClient() {
  if (this.client) {
    this.client.subscribe(this.topic);
  }
}

PhSensor.prototype.publishValue = function publishValue(value) {
  const message = {
    reported: {
      sensors: {
        ph: value
      }
    }
  }
  this.client.publish(this.topic, JSON.stringify(message));
}

PhSensor.prototype.deviceInfo = function deviceInfo() {
  this.ph.getInfo();
}

PhSensor.prototype.read = function read() {
  let value = this.ph.reading();
  if (value === -10) { // error reading the sensor
    // console.log('[phSensor] - reading error:', value);
    return this.prevValue;
  }
  const rounded = round(value, 2);
  if (this.client !== undefined && this.prevValue !== rounded) {
    this.publishValue(rounded.toString());
    this.prevValue = rounded;
  }
  return rounded;
}

PhSensor.prototype.enableMonitor = function enableEvents() {
  if (!this.eventInterval) {
    this.eventInterval = setInterval(() => {
      this.read();
    }, 2000);
  }
}

PhSensor.prototype.disableMonitor = function disableMonitor() {
  clearInterval(this.eventInterval);
  this.eventInterval = false;
}

const SensorCreator = (opt = {}) => {
  const { client, topic } = opt;
  const sensor = new PhSensor({ client, topic });
  // sensor.initClient();
  return sensor
}

module.exports = SensorCreator;
