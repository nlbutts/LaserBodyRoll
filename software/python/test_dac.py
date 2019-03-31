#!/usr/bin/python3
import time
import smbus

bus = smbus.SMBus(1)

out = 0
address = 0x60

while True:
   data = [out >> 8, out & 0xFF]
   bus.write_i2c_block_data(address, 0x00, data)
   bus.write_i2c_block_data(address, 0x08, data)
   out += 1
