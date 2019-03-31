#!/usr/bin/python3
from gpiozero import LED
from gpiozero import Button
import time

DIN = Button(15)
DOUT = LED(22)
PULLUP = LED(23)
RES = LED(18)

RES.on()

while True:
   DOUT.toggle()
   print(DIN.is_active)
   PULLUP.toggle()
   time.sleep(1)
