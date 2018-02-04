
extern "C" {
#include "vl53l0x_api.h"
}

namespace VL53L0X {

class vl53l0x
{
public:
    vl53l0x();
    virtual ~vl53l0x();
    int init();
    void disconnect();
    float getMeasurement();

private:
    void print_pal_error(VL53L0X_Error Status);
    void print_range_status(VL53L0X_RangingMeasurementData_t* pRangingMeasurementData);
    VL53L0X_Error configureDevice(VL53L0X_Dev_t *pMyDevice);


private:
    VL53L0X_Dev_t   _MyDevice;
    int32_t         _init_done;
    float           _lastLaserMeasurement;
    double          _millivoltsPerMillimeter;
    double          _zeroedLaserValueInMillimeteres;

};

}
