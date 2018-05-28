const Sensor = require('bindings')('PhSensor');

/**
 * Creates an instance of PhSensor.
 * @param {int} port The port number where this component us connected.
 * @param {int} add The second argument.
 * @returns {PhSensor}.
 */
function PhSensor(add = 0) {
  const self = this;
  // EventEmitter.call(this);
  this.ph = new Sensor(add);

  // process.on('SIGINT', () => {
  //   self.ph.release();
  // });
  //
  // process.on('SIGTERM', () => {
  //   self.ph.release();
  // });
}

PhSensor.prototype.deviceInfo = function deviceInfo() {
  this.ph.getInfo();
}

PhSensor.prototype.read = function deviceInfo() {
  return this.ph.reading();
}

module.exports = PhSensor;
