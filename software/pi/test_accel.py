import time
from laser_board import icm20602

icm = icm20602.ICM20602()

while True:
    print(icm.getAcceleration())
    print(icm.getTemperature())
    time.sleep(0.1)
