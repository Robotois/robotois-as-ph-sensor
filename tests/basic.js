const Sensor = require('../index.js');

const phSensor = new Sensor(0);

setTimeout(() => {
  console.log('phValue:', phSensor.read());
});

// phSensor.deviceInfo();
