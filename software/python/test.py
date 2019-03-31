#!/usr/bin/python3
from gpiozero import LED
from gpiozero import Button
import time
import spidev

RES = LED(18)

RES.on()

spi = spidev.SpiDev()
spi.open(0, 0)

while True:
   ret = spi.xfer2([0x0F, 0x00, 0x07])
   print(ret)
   time.sleep(1)
