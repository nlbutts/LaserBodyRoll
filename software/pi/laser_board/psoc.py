import spidev
import struct

class PSOC:

    def __init__(self):
        # Setup SPI
        self.spi = spidev.SpiDev()
        self.spi.open(0, 0)
        self.spi.max_speed_hz=400000
        self.msg_count = 0

    def updateVoltage(self, desiredVoltage):
        print("Sending data to PSOC")
        v = struct.pack('>H', int(desiredVoltage * 1000))
        txdata = [0x55, 0xAA, v[0], v[1], 0]
        txdata.append(self.calculateChecksum(txdata))
        rxdata = self.spi.xfer(txdata)
        self.msg_count += 1
        print('Message count: {0}'.format(self.msg_count))
        print('[{}]'.format(', '.join(hex(x) for x in rxdata)))

    def calculateChecksum(self, data):
        checksum = 0
        for d in data:
            checksum += d
        return checksum