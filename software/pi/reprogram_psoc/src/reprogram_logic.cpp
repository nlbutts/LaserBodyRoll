#include <string>
#include <iostream>
#include <cstring>
#include <time.h>

extern "C" {
#include "cybtldr_api.h"
#include "cybtldr_api2.h"
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

int openSPI(void)
{
    uint8_t temp[50];
    int err = wiringPiSPISetup(0, 1000000);
    //wiringPiSPIDataRW(0, temp, 32);
    //usleep(500000);
    cout << "wiringPiSPISetup: " << err << endl;

    return CYRET_SUCCESS;
}

int closeSPI()
{
    cout << "Close SPI called" << endl;
    return CYRET_SUCCESS;

}

int readData(uint8_t *buf, int length)
{
    //cout << "readData length: " << length << endl;
    std::memset(buf, 0, length);
    uint8_t temp;
    do
    {
        usleep(1000);
        int err = wiringPiSPIDataRW(0, &temp, 1);
    } while (temp == 0xFF);

    int err = wiringPiSPIDataRW(0, &buf[1], length - 1);
    buf[0] = temp;

    // for (int i = 0; i < length; i++)
    // {
    //     printf("%02X ", buf[i]);
    // }
    // printf("\n");
    usleep(1000);

    return CYRET_SUCCESS;
}

int writeData(uint8_t *buf, int length)
{
    //cout << "writeData length: " << length << endl;
    // for (int i = 0; i < length; i++)
    // {
    //     printf("%02X ", buf[i]);
    // }
    // printf("\n");
    int err = wiringPiSPIDataRW(0, buf, length);
    return CYRET_SUCCESS;
}

void updateStatus(uint8_t arrayId, uint16_t rowNum)
{
    cout << "arrayId: " << (int)arrayId << " rowNum: " << rowNum << endl;
}


void programPsoC(std::string inputFile)
{
    CyBtldr_CommunicationsData comm;
    comm.OpenConnection     = openSPI;
    comm.CloseConnection    = closeSPI;
    comm.ReadData           = readData;
    comm.WriteData          = writeData;
    comm.MaxTransferSize    = 32;

    CyBtldr_Program(inputFile.c_str(), 0, 1, &comm, updateStatus);
}

