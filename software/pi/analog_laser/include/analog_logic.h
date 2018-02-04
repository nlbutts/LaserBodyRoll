#include <string>

/**
* This function reads the laser distance and then sends a command to control the analog output distance
*
* @param updateRateMs the desired update rate in milliseconds
* @param configFile the configuration file for the various settings
*/
void runAnalogLaser(int updateRateMs, std::string configFile);
