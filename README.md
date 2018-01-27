# LaserBodyRoll

This product is designed to simulate wheel slip to prevent the front of a car from rising off the ground during hard acceleration. The device would be connected in between a wheel speed sensor and an engine ECU. Under normal conditions the device would pass through the wheel speed sensor directly to the engine ECU. If the front of the vehicle is detected rising off the ground, the system would increase the number of pulses per second (PPS) of the wheel to the engine ECU to simulate wheel slip. In theory, this should cause the engine ECU to reduce timing to prevent the simulated wheel slip and therefore reduce the front end from rising off the ground.
The system detects front end rise by using a laser rangefinder. The laser rangefinder can detect the small changes in distance from the mounting location to the ground. If the distance is increasing, then the system can increase the number of PPS from the wheel speed sensor to simulate the slip.

![Architecture](https://github.com/adam-p/markdown-here/raw/master/src/common/images/icon48.png "High Level Architecture")


# Hardware Connections
The system will have three connectors: 1) to ECU connector, 2) to sensor connector, 3) USB connector. The ECU connector will supply power to the box, and provide the speed sensor signal back to the ECU. The sensor connector will provide power to the sensor and receive the PPS signal. The USB connector will be used for reprogramming and configuration.
ECU Connector

| Pin | Description     |
| --- | -----------     |
| 1   | Power           |
| 2   | Ground          |
| 3   | Voltage Output  |
| 4   | Button input    |
