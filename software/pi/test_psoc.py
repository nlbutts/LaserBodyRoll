import time
from laser_board import psoc

p = psoc.PSOC()

voltage = 0

while (True):
    p.updateVoltage(voltage);
    time.sleep(0.2)
    voltage += 0.1
