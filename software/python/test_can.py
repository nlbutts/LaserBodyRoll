#!/usr/bin/python3
from gpiozero import LED
from gpiozero import Button
import time
import spidev

class MCP25625():
   def __init__(self, clk):
      self.clk = clk
      self.reset = LED(18)
      self.TxReq = LED(14)
      self.CanInt = Button(24)
      self.spi = spidev.SpiDev()
      self.spi.open(0, 0)

   def setMode(self, mode):
      value = mode << 5 | 0x7
      self.spi.xfer2([0x20, 0x0F, value])

   def resetChip(self):
      self.reset.off()
      time.sleep(0.1)
      self.reset.on()

   def transmit(self):
      self.TxReq.on()
      time.sleep(0.1)
      self.TxReq.off()

   def printStatus(self):
      ret = self.spi.xfer2([0x03, 0x0F, 0x00])
      control_reg = ret[2]
      ret = self.spi.xfer2([0xA0, 0x00, 0x00])
      status = ret[2]
      ret = self.spi.xfer2([0xB0, 0x00, 0x00])
      rx_status = ret[2]

      print("CANCTRL: {:X} - STATUS: {:X} - RX_STATUS: {:X}".format(control_reg, status, rx_status))

   def configure(self, PRSEG, PHSEG1, PHSEG2):
      # Write CNF1
      ret = self.spi.xfer2([0x20, 0x2A, 0x00])
      # Write CNF2
      value = (PHSEG1 - 1) << 3 | (PRSEG - 1)
      ret = self.spi.xfer2([0x20, 0x29, value])
      # Write CNF3
      value = PHSEG2 - 1
      ret = self.spi.xfer2([0x20, 0x28, value])
      # Use B0RTSM to transmit a CAN message
      ret = self.spi.xfer2([0x20, 0x0D, 0x01])

   def configure_rx(self):
      # Set Receive acceptance mask to 0
      ret = self.spi.xfer2([0x20, 0x20, 0x00])
      ret = self.spi.xfer2([0x20, 0x24, 0x00])
      # Setup receive buffer
      ret = self.spi.xfer2([0x20, 0x60, 0x60])

   def setTxObject(self, id, data):
      buf = []
      buf.append(0x40)
      buf.append(id >> 3)
      buf.append((id & 0x08) << 5)
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


can = MCP25625(8000000)
can.resetChip()
can.printStatus()
can.setMode(4)
can.printStatus()
can.configure(5, 8, 2)
can.configure_rx()
can.printStatus()
can.setMode(2)
can.setTxObject(0x123, [0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF])

while True:
   can.printStatus()
   time.sleep(1)
   can.transmit()
