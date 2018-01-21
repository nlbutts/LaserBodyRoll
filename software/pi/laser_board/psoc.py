import spidev

class PSOC:

    def __init__(self):
        # Setup SPI
        self.spi = spidev.SpiDev()
        self.spi.open(0, 0)
        self.spi.max_speed_hz=400000
        self.msg_count = 0

    def test(self):
        print("Sending data to PSOC")
        txdata = [0xDE, 0xAD, 0xBE, 0xEF]
        rxdata = self.spi.xfer(txdata)
        self.msg_count += 1
        print('Message count: {0}'.format(self.msg_count))
        print('[{}]'.format(', '.join(hex(x) for x in rxdata)))
