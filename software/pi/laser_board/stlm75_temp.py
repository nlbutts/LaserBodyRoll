import smbus

class STLM75_Temp:

    DEVICE_ADDR     = 0x48
    REG_TEMP        = 0
    REG_CONFIG      = 1
    REG_HYSTERESIS  = 2
    REG_OVERTEMP    = 3

    def __init__(self):
        # Write the configuration register
        self.bus = smbus.SMBus(1)
        self.bus.write_byte(self.DEVICE_ADDR, self.REG_TEMP)

    def getTemperature(self):
        data = self.bus.read_word_data(self.DEVICE_ADDR, 0)
        temp = data & 0xFF
        temp <<= 1
        if (data & 0x8000):
            temp |= 1
        return temp / 2
