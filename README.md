# LaserBodyRoll

This product is designed to simulate wheel slip to prevent the front of a car from rising off the ground during hard acceleration. The device would be connected in between a wheel speed sensor and an engine ECU. Under normal conditions the device would pass through the wheel speed sensor directly to the engine ECU. If the front of the vehicle is detected rising off the ground, the system would increase the number of pulses per second (PPS) of the wheel to the engine ECU to simulate wheel slip. In theory, this should cause the engine ECU to reduce timing to prevent the simulated wheel slip and therefore reduce the front end from rising off the ground.
The system detects front end rise by using a laser rangefinder. The laser rangefinder can detect the small changes in distance from the mounting location to the ground. If the distance is increasing, then the system can increase the number of PPS from the wheel speed sensor to simulate the slip.

![Architecture](https://github.com/nlbutts/LaserBodyRoll/blob/master/Documentation/Architecture.bmp "High Level Architecture")


# Hardware Connections
The system will have three connectors: 1) to ECU connector, 2) to sensor connector, 3) USB connector. The ECU connector will supply power to the box, and provide the speed sensor signal back to the ECU. The sensor connector will provide power to the sensor and receive the PPS signal. The USB connector will be used for reprogramming and configuration.
ECU Connector

| Pin | Description     |
| --- | -----------     |
| 1   | Power           |
| 2   | Ground          |
| 3   | Voltage Output  |
| 4   | Button input    |

# Protocol between PSoC and Raspberry Pi
The PSoC and the Raspberry PI are connected via an SPI bus. The Pi is the SPI Master and the PSoC is a slave device. The packet that is transmitted to the PSOC is shown below

| Byte | Description |
| ---- | ------------|
| 1    | Sync1 = 0x55 |
| 2    | Sync2 = 0xAA |
| 3    | Output Voltage MSB |
| 4    | Output Voltage LSB |
| 4    | Setting Bits |
| 5    | Checksum |

## Output Voltage
The output voltage is a 16-bit value where each bit represents a millivolt. So a value of 100 would be a desired output of 100 millivolts. A value of 9876 would be a desired output of 9.876 volts.

## Bits

| Bit | Description |
| --- | ------------|
| 1   | Set digital out 1 high |
| 2   | Set digital out 2 high |
| 3   | Reserved |
| 4   | Reserved |
| 5   | Reserved |
| 6   | Reserved |
| 7   | Jump to bootblock |
| 8   | Jump to bootblock |

To jump to bootblock 4 packets need to be send where the jump to bootblock values count from 0 to 3. Once the fourth value is received it will jump to bootblock.

The packet the PSoC sends back is shown below.

| Byte | Description |
| ---- | ------------|
| 1    | Sync1 = 0x55 |
| 2    | Sync2 = 0xAA |
| 3    | Input Voltage MSB |
| 4    | Input Voltage LSB |
| 4    | Status Bits |
| 5    | Checksum |

## Input Voltage
Input voltage is the input voltage signal in millivolts. This is currently not implemented

## Status Bits
| Bit | Description |
| --- | ------------|
| 1   | Digital input 1 status |
| 2   | Digital input 2 status |
| 3   | Reserved |
| 4   | Reserved |
| 5   | Reserved |
| 6   | Reserved |
| 7   | Reserved |
| 8   | Reserved |
