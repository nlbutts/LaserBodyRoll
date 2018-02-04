#include <string>
#include <iostream>
#include <cstring>
#include <time.h>

#include "analog_logic.h"
#include "vl53l0x.h"

extern "C" {
#include <wiringPiSPI.h>
}
using namespace std;

void usleep(int microseconds)
{
    struct timespec tm;
    if (microseconds >= 1000000)
    {
        tm.tv_sec = microseconds / 1000000;
        tm.tv_nsec = microseconds - (tm.tv_sec * 1000000);
        tm.tv_nsec *= 1000;
    }
    else
    {
        tm.tv_sec = 0;
        tm.tv_nsec = microseconds * 1000;
    }

    nanosleep(&tm, NULL);
}

void runAnalogLaser(int updateRate, std::string configFile)
{
    VL53L0X::vl53l0x laser;

    while (1)
    {
        cout << "Laser distance " << laser.getMeasurement() << " mm" << endl;
    }
}

