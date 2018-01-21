import time
from laser_board import psoc

p = psoc.PSOC()

while (True):
    p.test();
    time.sleep(0.2)
