#!/usr/bin/python3
import smbus
import time

class ICM20602():
    def __init__(self, address):
        """Initialized the ICM20602 to 10 Hz mode

        Args:
            address (int): I2C address of the DAC.
        """
        self.address = address
        self.bus = smbus.SMBus(1)
        self.packet_size = int(14)

        #DEVICE RESET -- Set bit 7 of PWR_MGMT_1 to High to reset registers to default
        success = False
        while success == False:
            time.sleep(0.1)
            try:
                #WHO_AM_I Register -- should be x12
                who_am_i = self.bus.read_byte_data(self.address, 0x75)
                print("WHO_AM_I: {:X}".format(who_am_i))
                time.sleep(0.1)
                ret = self.bus.write_byte_data(self.address, 0x6B, 0x80)
                time.sleep(0.1)
                success = True
                pass
            except Exception as e:
                print("I2C error, retrying")
                print(e)

        #PWR_MGMT_1 & 2 -- set 1 to x01 to wake, 2 should be x00 to ensure all sensors are on
        self.bus.write_byte_data(self.address, 0x6B, 0x01)
        pwr1 = self.bus.read_byte_data(self.address, 0x6B)
        pwr2 = self.bus.read_byte_data(self.address, 0x6C)
        print("PWR_MGMT_1: {:X}, PWR_MGMT_2: {:X}".format(pwr1, pwr2))

        #CONFIG Register -- set to x01 to signal user config and allow FIFO overwrites
        self.bus.write_byte_data(self.address, 0x1A, 0x01);
        config = self.bus.read_byte_data(self.address, 0x1A)
        print("CONFIG: {:X}".format(config))

        #FIFO_EN Register -- set to x18 to enable GYRO and ACCEL in FIFO
        self.bus.write_byte_data(self.address, 0x23, 0x18)
        fifo_en = self.bus.read_byte_data(self.address, 0x23)
        print("FIFO_EN: {:X}".format(fifo_en))

        #SMPLRT_DIV Register -- set to specified value at beginning of file
        self.bus.write_byte_data(self.address, 0x19, 99)
        smplrt = self.bus.read_byte_data(self.address, 0x19)
        print("SMPLRT_DIV: {:X}".format(smplrt))

        # Set the accelerometer sensitivity to 8g
        self.bus.write_byte_data(self.address, 0x1C, 0x08)

        # Set the low pass filter for the accelerometer
        self.bus.write_byte_data(self.address, 0x1D, 5)

        # Set the low pass filter for the gyro
        self.bus.write_byte_data(self.address, 0x1D, 5)

        # USER_CTRL Register -- set to x44 to enable FIFO operation and clear FIFO
        # will reset to x40 after clear is complete
        self.bus.write_byte_data(self.address, 0x6A, 0x44)
        user_ctrl = self.bus.read_byte_data(self.address, 0x6A)
        print("USER_CTRL: {:X}".format(user_ctrl))

    def icm_20602_dumpFIFO(self):
        timestamp = 0
        while True:
            intStatus = self.bus.read_byte_data(self.address, 0x3A)
            overflow = intStatus & 0x10;

            if overflow:
                print("!!!OVERFLOW")

            countH = self.bus.read_byte_data(self.address, 0x72)
            countL = self.bus.read_byte_data(self.address, 0x73)
            fifo_size = int((countH << 8) + countL)
            num_packets = int(fifo_size / self.packet_size)

            fepoch = time.time()
            timestamp += 1

            if num_packets > 0:
                data = self.bus.read_i2c_block_data(self.address, 0x74, int(num_packets * self.packet_size))

                for packet_index in range(num_packets):
                    offset = packet_index * self.packet_size;
                    temperature = ((int(data[offset +  6])) << 8) + data[offset +  7]
                    tempConversion = float(temperature)
                    tempConversion /= 326.8
                    tempConversion += 25

                    accelx = ((int(data[offset +  0])) << 8) + data[offset +  1]
                    accely = ((int(data[offset +  2])) << 8) + data[offset +  3]
                    accelz = ((int(data[offset +  4])) << 8) + data[offset +  5]

                    gyrox = ((int(data[offset +  8])) << 8) + data[offset +  9]
                    gyroy = ((int(data[offset + 10])) << 8) + data[offset + 11]
                    gyroz = ((int(data[offset + 12])) << 8) + data[offset + 13]

                    print("{:}, {:}, {:}, {:}, {:}, {:}, {:}, {:}, {:}, {:}, {:}".format(
                             fepoch,
                             timestamp,
                             accelx,
                             accely,
                             accelz,
                             tempConversion,
                             gyrox,
                             gyroy,
                             gyroz,
                             overflow,
                             num_packets))
