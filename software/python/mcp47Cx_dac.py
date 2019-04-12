#!/usr/bin/python3
import smbus

class MCP47CX():
    def __init__(self, address, vref):
        """Initialized the DAC object with the I2C address.

        Args:
            address (int): I2C address of the DAC.
            vref (float): The reference voltage
        """
        self.address = address
        self.vref = vref
        self.bus = smbus.SMBus(1)

    def set_voltage(self, channel, value):
        """Sets the output voltage for a particular channel

        Args:
            channel (int): Channel 0 or 1
            value (float): The output in volts
        """
        if channel == 0:
            reg = 0
        else:
            reg = 0x08

        dac_value = int(((value / self.vref) * 2 ** 12) + 0.5)
        print(dac_value)
        dac_value = int(dac_value)

        data = [dac_value >> 8, dac_value & 0xFF]
        self.bus.write_i2c_block_data(self.address, reg, data)

