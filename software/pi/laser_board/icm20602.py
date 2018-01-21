import smbus
import struct
import numpy as np

class ICM20602:

    # Device I2C address
    DEVICE_ADDR         = 0x69

    # Register definitions
    REG_POWER_MGMT      = 107
    REG_ACCEL_X_MSB     = 59
    REG_ACCEL_X_LSB     = 60
    REG_ACCEL_Y_MSB     = 61
    REG_ACCEL_Y_LSB     = 62
    REG_ACCEL_Z_MSB     = 63
    REG_ACCEL_Z_LSB     = 64
    REG_TEMP_MSB        = 65
    REG_TEMP_LSB        = 66

    REG_ACCEL_OFFSET_X_MSB = 119
    REG_ACCEL_OFFSET_X_LSB = 120
    REG_ACCEL_OFFSET_Y_MSB = 122
    REG_ACCEL_OFFSET_Y_LSB = 123
    REG_ACCEL_OFFSET_Z_MSB = 125
    REG_ACCEL_OFFSET_Z_LSB = 126

    # Constants
    DEFAULT_ACCEL_G     = 2
    MG_PER_BIT          = (DEFAULT_ACCEL_G) / 32768
    ACCEL_OFFSET_ADJUST = 0.98
    TEMP_SENSITIVITY    = 326.8
    TEMP_OFFSET         = 0

    def __init__(self):
        # Write the configuration register
        self.bus = smbus.SMBus(1)
        self.bus.write_byte_data(self.DEVICE_ADDR, self.REG_POWER_MGMT, 0)
        b = self.bus.read_i2c_block_data(self.DEVICE_ADDR, self.REG_ACCEL_OFFSET_X_MSB, 2)
        xoffset = np.array(struct.unpack('>h', bytearray(b)), dtype='float')
        b = self.bus.read_i2c_block_data(self.DEVICE_ADDR, self.REG_ACCEL_OFFSET_Y_MSB, 2)
        yoffset = np.array(struct.unpack('>h', bytearray(b)), dtype='float')
        b = self.bus.read_i2c_block_data(self.DEVICE_ADDR, self.REG_ACCEL_OFFSET_Z_MSB, 2)
        zoffset = np.array(struct.unpack('>h', bytearray(b)), dtype='float')
        # Converting to 15-bit data, the LSB is always zero
        self.accel_offsets_in_mg = np.array((xoffset[0], yoffset[0], zoffset[0]), dtype='float')
        self.accel_offsets_in_mg /= 2
        self.accel_offsets_in_mg *= self.ACCEL_OFFSET_ADJUST
        print('Acceleration offsets: {0}'.format(self.accel_offsets_in_mg))

    def getAcceleration(self):

        b = self.bus.read_i2c_block_data(self.DEVICE_ADDR, self.REG_ACCEL_X_MSB, 6)
        accel = np.array(struct.unpack('>hhh', bytearray(b)), dtype='float')
        accel += self.accel_offsets_in_mg
        accel *= self.MG_PER_BIT
        return accel

    def getTemperature(self):
        b = self.bus.read_i2c_block_data(self.DEVICE_ADDR, self.REG_TEMP_MSB, 2)
        temp = np.array(struct.unpack('>h', bytearray(b)), dtype='float')
        temp / self.TEMP_SENSITIVITY + self.TEMP_OFFSET
        return temp

