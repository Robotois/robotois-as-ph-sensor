const Sensor = require('../');

const phSensor = Sensor();

setInterval(() => {
  console.log('phValue:', phSensor.read());
}, 50);

// phSensor.deviceInfo();
