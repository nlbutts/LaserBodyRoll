#include <stdint.h>

namespace Embedded {
namespace Sensors {


/**
 * @brief Range Finder interface
 * @details This is a generic interface to a range finder system.
 */
class IRangeFinder
{
public:
    ~IRangeFinder() {};
    /**
     * @brief This function initializes the range finder system
     * @details This should be called once on power to initialize the range finder system.
     *
     * @return bool true if successful, false otherwise
     */
    virtual bool initialize() = 0;
    /**
     * @brief Starts the range finder
     * @details After initializing the range find the start function shold be called.
     * If a low power mode exists, the sensor could be in a low power mode
     * until start is called. Once start is called the sensor should start
     * reading on a periodic basis
     *
     * @return bool true if successful, false otherwise
     */
    virtual bool start() = 0;
    /**
     * @brief Stop the sensor
     * @details Call this function to stop the sensor or put it in some sort
     * of low power mode
     *
     * @return bool true if successful, false otherwise
     */
    virtual bool stop() = 0;
    /**
     * @brief Periodic execute function
     * @details This is a periodic execute function, although a periodic
     * timer could be setup in the start function to perform the required
     * activities.
     *
     */
    virtual void run() = 0;
    /**
     * @brief Returns the latest distance reading
     * @details This function will return the last measurement distance in
     * millimeters
     *
     * @return int32_t positive numbers represent the distance in millimeters
     * a negative number is an error code.
     */
    virtual int32_t getDistanceInMillimeters() const = 0;

protected:
    IRangeFinder() {};
};

} // Sensors
} // Embedded
