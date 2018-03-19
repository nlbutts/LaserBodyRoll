
#include "embedded/sensors/IRangeFinder.h"
#include "libst_config.h"
#include "vl53l0x_api.h"


namespace STSensors {

class VL53L0X : public Embedded::Sensors::IRangeFinder
{
public:
    VL53L0X(I2C_HandleTypeDef &i2c);
    ~VL53L0X();

    /**
     * @brief This function initializes the range finder system
     * @details This should be called once on power to initialize the range finder system.
     *
     * @return bool true if successful, false otherwise
     */
    bool initialize();
    /**
     * @brief Starts the range finder
     * @details After initializing the range find the start function shold be called.
     * If a low power mode exists, the sensor could be in a low power mode
     * until start is called. Once start is called the sensor should start
     * reading on a periodic basis
     *
     * @return bool true if successful, false otherwise
     */
    bool start();
    /**
     * @brief Stop the sensor
     * @details Call this function to stop the sensor or put it in some sort
     * of low power mode
     *
     * @return bool true if successful, false otherwise
     */
    bool stop();
    /**
     * @brief Periodic execute function
     * @details This is a periodic execute function, although a periodic
     * timer could be setup in the start function to perform the required
     * activities.
     *
     */
    void run();
    /**
     * @brief Returns the latest distance reading
     * @details This function will return the last measurement distance in
     * millimeters
     *
     * @return int32_t positive numbers represent the distance in millimeters
     * a negative number is an error code.
     */
    int32_t getDistanceInMillimeters() const    {return _latestMeasurement;}

private:
    void print_pal_error(VL53L0X_Error Status);


private:
    I2C_HandleTypeDef  *_i2c;
    bool                _initialized;
    VL53L0X_Dev_t       _stLaser;
    int32_t             _latestMeasurement;

};

} // namespace STSensors