#!/usr/bin/python3
from gpiozero import LED
from gpiozero import Button
import time
import spidev

"""This is a class for the MCP25625 CAN controller/transceiver.
   It supports transmits, receives, configurations. It needs work.

"""
class MCP25625():
   def __init__(self, crystal, max_speed_hz, reset_pin = 18, tx_req_pin = 14, int_pin = 24):
      """Initialized object with the crystal frequency and the max SPI
      bus frequency

      Args:
         crystal (int): The frequency of the crystal attached to the controller
         max_speed_hz (int): The max speed of the SPI bus
         reset_pin (int): The BCM pin number connected to the reset line
         tx_req_pin (int): The BCM pin number connected to the Tx request line
         int_pint (int): The BCM pin number connected to the interrupt pin (input)
      """
      self.crystal = crystal
      self.reset = LED(reset_pin)
      self.TxReq = LED(tx_req_pin)
      self.CanInt = Button(int_pin)
      self.spi = spidev.SpiDev()
      self.spi.open(0, 0)
      self.spi.max_speed_hz = max_speed_hz

      self.mode_normal   = 0
      self.mode_sleep    = 1
      self.mode_loopback = 2
      self.mode_listen   = 3
      self.mode_config   = 4


   def setMode(self, mode):
      """Sets the mode of the controller, use the mode definitions above

      Args:
         mode (int): The mode definitions defined above in this class
      """
      value = mode << 5 | 0x7
      self.spi.xfer2([0x05, 0x0F, 0xFF, value])

   def resetChip(self):
      """Forces a reset of the CAN controller
      """
      self.reset.off()
      time.sleep(0.1)
      self.reset.on()

   def transmit(self):
      """Toggle the Tx request pin for Transmit object 1
      """
      self.TxReq.on()
      time.sleep(0.1)
      self.TxReq.off()

   def printStatus(self):
      """Debug function that prints the various status values of the CAN controller
      """
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

      ret = self.spi.xfer2([0x03, 0x2D, 0x00])
      errors = ret[2]

      print("CANCTRL: {:X} - CANSTATUS: {:X} - STATUS: {:X} - RX_STATUS: {:X} - TEC: {:} - REC: {:} - ERRORS: {:X}".format(control_reg, canstat, status, rx_status, TEC, REC, errors))

   def configure(self, PRSEG, PHSEG1, PHSEG2):
      """Configures the time quanta, refer to the datasheet

      Args:
         PRSEG (int): The pre sync TQ
         PHSEG1 (int): The seg 1 TQ
         PHSEG2 (int): The seg 2 TQ
      """
      # Write CNF1
      ret = self.spi.xfer2([0x05, 0x2A, 0xFF, 0xC0])
      # Write CNF2
      value = (PHSEG1 - 1) << 3 | (PRSEG - 1)
      ret = self.spi.xfer2([0x05, 0x29, 0xFF, value])
      # Write CNF3
      value = PHSEG2 - 1
      ret = self.spi.xfer2([0x05, 0x28, 0xFF, value])
      # Use B0RTSM to transmit a CAN message
      ret = self.spi.xfer2([0x05, 0x0D, 0xFF, 0x01])

   def configure_rx_masks(self):
      """This function needs more work, if configures the mask to receive all CAN messages
      """
      # Set Receive acceptance mask to 0
      ret = self.spi.xfer2([0x20, 0x20, 0x00])
      ret = self.spi.xfer2([0x20, 0x24, 0x00])
      # Setup receive buffer
      ret = self.spi.xfer2([0x20, 0x60, 0x60])

   def setTxObject(self, id, data):
      """Sets Tx object 1 with the ID and data

      Args:
         id (int): The 11-bit or 29-bit CAN id (currently only supports 11-bit)
         data (int): zero to eight bytes of data to transmit
      """
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
      """Debug function to print one of the receive CAN buffers

      Args:
         obj (int): Which CAN Rx object to print
      """
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
      """Returns True if a CAN message has been received and which buffer it was received in

      Returns:
         int: -1 no message, 0 message in buffer 0, 1 message in buffer 1
      """

      # Read Rx Status
      ret = self.spi.xfer2([0xB0, 0x00, 0x00])
      rx_status = ret[2]
      if (rx_status & 0x80):
         return 0
      elif (rx_status & 0x40):
         return 1
      return -1

   def printAddress(self, address, length):
      """Debug function that prints data from address to address + length

      Args:
         address (int): The starting address to print
         length (int): The length of registers to print
      """
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


