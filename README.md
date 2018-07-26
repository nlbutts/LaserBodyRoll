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

The goal is to fit into this ![box](https://www.digikey.com/product-detail/en/bud-industries/PN-1320-CMB/377-1887-ND/2674151 "enclosure")

# Protocol between Processor and BLE
The PSoC and the Raspberry PI are connected via an SPI bus. The Pi is the SPI Master and the PSoC is a slave device. The packet that is transmitted to the PSOC is shown below

| Sync1 (8) | Sync2 (8) | Version (4)/Msg ID (4) | Length (8) | payload (2040) | CRC (8) |
| --------- | --------- | ---------------------- | ---------- | -------------- | ------- |
| 0x55      | 0xAA      | 0x01 / MSG ID          |            |                |         |

The number in parenthesis is how many bits are used for the various fields
The 4-bits of the version allows updates to the protocol. The 4-bits for the message ID allows
128 different message IDs. Length is the number of bytes in the payload 0-255 bytes.
The CRC is the CRC-8-CCITT using the following generator polynominal:
x^8 + x^2 + x + 1 (0x7)


| MSG ID | Description |
| ------ | ------------|
| 0      | Data input  |
| 1      | Data output |
| 2      | Main programming image |
| 3      | BLE programming image  |

Data input is a generic pass through message from the BLE interface to the main processor. The
data input is made up of an 8-bit UUID followed by the data item. Each data item has a unique
length, format, scale, etc. Data output is the same as data input, just going in the other
direction

| UUID | Description             | Size (bytes) | Data type | Units |
| ---- | ----------------------- | ------------ | --------- | ----- |
| 0    | Analog 1 slope          | 4            | float     | mm/mv |
| 1    | Analog 1 y offset       | 4            | float     | mv    |
| 2    | Analog 2 slope          | 4            | float     | mm/mv |
| 3    | Analog 2 y offset       | 4            | float     | mv    |
| 4    | Open drain pull up enbl | 1            | uint8     | bool  |
| 5    | Laser distance in mm    | 2            | uint16    | mm    |
| 6    | Accel X in mg           | 2            | uint16    | mg    |
| 7    | Accel Y in mg           | 2            | uint16    | mg    |
| 8    | Accel Z in mg           | 2            | uint16    | mg    |
| 9    | Gyro X in dps           | 2            | uint16    | dps   |
| 10   | Gyro Y in dps           | 2            | uint16    | dps   |
| 11   | Gyro Z in dps           | 2            | uint16    | dps   |
| 12   | Auto level gain         | 4            | float     |       |
| 13   | EPOCH time              | 4            | uint32    | epoch |
| 14   | Super cap voltage       | 2            | uint32    | mv    |



The main programming image is a LZMA compressed binary file. The BLE programming
image is an LZMA compressed cyacd file. Each BLE packet is only 23 bytes or so.
The programming images are transmitted with a byte counter as the first byte
of the payload. This allows a check that a packet hasn't been dropped and they are being
received in the correct order.