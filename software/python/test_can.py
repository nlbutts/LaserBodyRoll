#!/usr/bin/python3
from gpiozero import LED
from gpiozero import Button
import time
import spidev

class MCP25625():
   def __init__(self, clk, max_speed_hz):
      self.clk = clk
      self.reset = LED(18)
      self.TxReq = LED(14)
      self.CanInt = Button(24)
      self.spi = spidev.SpiDev()
      self.spi.open(0, 0)
      self.spi.max_speed_hz = max_speed_hz

   def setMode(self, mode):
      value = mode << 5 | 0x7
      self.spi.xfer2([0x05, 0x0F, 0xFF, value])

   def resetChip(self):
      self.reset.off()
      time.sleep(0.1)
      self.reset.on()

   def transmit(self):
      self.TxReq.on()
      time.sleep(0.1)
      self.TxReq.off()

   def printStatus(self):
      # Read CANCTRL
      ret = self.spi.xfer2([0x03, 0x0F, 0x00])
      control_reg = ret[2]
      # Read Status
      ret = self.spi.xfer2([0xA0, 0x00, 0x00])
      status = ret[2]
      # Read Rx Status
      ret = self.spi.xfer2([0xB0, 0x00, 0x00])
      rx_status = ret[2]
      # Read CANSTAT
      ret = self.spi.xfer2([0x03, 0x0E, 0x00])
      canstat = ret[2]
      # Read TEC and REC
      ret = self.spi.xfer2([0x03, 0x1C, 0x00, 0x00])
      TEC = ret[2]
      REC = ret[3]

      print("CANCTRL: {:X} - CANSTATUS: {:X} - STATUS: {:X} - RX_STATUS: {:X} - TEC: {:} - REC: {:}".format(control_reg, canstat, status, rx_status, TEC, REC))

   def configure(self, PRSEG, PHSEG1, PHSEG2):
      # Write CNF1
      ret = self.spi.xfer2([0x05, 0x2A, 0xFF, 0x00])
      # Write CNF2
      value = (PHSEG1 - 1) << 3 | (PRSEG - 1)
      ret = self.spi.xfer2([0x05, 0x29, 0xFF, value])
      # Write CNF3
      value = PHSEG2 - 1
      ret = self.spi.xfer2([0x05, 0x28, 0xFF, value])
      # Use B0RTSM to transmit a CAN message
      ret = self.spi.xfer2([0x05, 0x0D, 0xFF, 0x01])

   def configure_rx(self):
      # Set Receive acceptance mask to 0
      ret = self.spi.xfer2([0x20, 0x20, 0x00])
      ret = self.spi.xfer2([0x20, 0x24, 0x00])
      # Setup receive buffer
      ret = self.spi.xfer2([0x20, 0x60, 0x60])

   def setTxObject(self, id, data):
      buf = []
      buf.append(0x02)
      buf.append(0x31)
      buf.append((id >> 3) & 0xFF)
      buf.append((id & 0x07) << 5)
      buf.append(0)
      buf.append(0)
      buf.append(0x08)

      # Data
      buf.append(data[0])
      buf.append(data[1])
      buf.append(data[2])
      buf.append(data[3])
      buf.append(data[4])
      buf.append(data[5])
      buf.append(data[6])
      buf.append(data[7])
      self.spi.xfer2(buf)

   def printRxObject(self, obj):
      buf = []
      buf.append(0x03)
      buf.append(0x61 | obj << 5)
      for i in range(13):
         buf.append(0)
      ret = self.spi.xfer2(buf)
      canid = ret[2] << 3
      canid |= (ret[3] >> 5) & 0x7
      length = ret[6] & 0xF
      formatStr = "{:X} - ".format(canid)
      for i in range(0, length):
         formatStr = "{:} {:X}".format(formatStr, ret[7 + i])

      print(formatStr)

   def rxMessageAvailable(self):
      # Read Rx Status
      ret = self.spi.xfer2([0xB0, 0x00, 0x00])
      rx_status = ret[2]
      if (rx_status & 0x80):
         return 0
      elif (rx_status & 0x40):
         return 1
      return -1

   def printAddress(self, address, length):
      buf = []
      buf.append(0x03)
      buf.append(address)
      for i in range(length):
         buf.append(0)

      ret = self.spi.xfer2(buf)
      temp = ""
      for v in ret:
         temp = "{:} {:X}".format(temp, v)

      print(temp)


can = MCP25625(8000000, 1000000)
can.resetChip()
can.printStatus()
can.setMode(4)
can.configure(5, 8, 2)
can.configure_rx()
can.setMode(0)
can.setTxObject(0x123, [0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF])
can.printAddress(0x30, 16)
can.printStatus()

while True:
   can.printStatus()
   time.sleep(1)
   can.transmit()
   rxObjAvailable = can.rxMessageAvailable()
   if rxObjAvailable >= 0:
      print("Rx message received object {:}".format(rxObjAvailable))
      can.printRxObject(rxObjAvailable)
