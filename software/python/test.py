#!/usr/bin/python3
from gpiozero import LED
from gpiozero import Button
import time
from mcp25625_can import MCP25625
from mcp47Cx_dac import MCP47CX
from icm20602 import ICM20602

DIN = Button(15)
DOUT = LED(22)
PULLUP = LED(23)

can = MCP25625(8000000, 1000000)
can.resetChip()
can.printStatus()
can.setMode(can.mode_config)
can.configure(7, 4, 4)
can.configure_rx_masks()
can.setMode(can.mode_normal)
can.setTxObject(0x123, [0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF])
can.printAddress(0x30, 16)
can.printStatus()

print("Setting up DAC")
dac = MCP47CX(0x60, 5.0)

imu = ICM20602(0x68)
imu.icm_20602_dumpFIFO()

while True:
    dac.set_voltage(0, 2.0)
    DOUT.toggle()
    print(DIN.is_active)
    PULLUP.toggle()

    can.printStatus()
    time.sleep(1)
    can.transmit()
    rxObjAvailable = can.rxMessageAvailable()
    if rxObjAvailable >= 0:
      print("Rx message received object {:}".format(rxObjAvailable))
      can.printRxObject(rxObjAvailable)

