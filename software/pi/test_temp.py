import time
from laser_board import stlm75_temp

t = stlm75_temp.STLM75_Temp()

while True:
    print(t.getTemperature())
    time.sleep(0.1)
