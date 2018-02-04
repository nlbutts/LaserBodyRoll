#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
#include "tclap/CmdLine.h"
#include "analog_logic.h"

using namespace TCLAP;
using namespace std;

int main(int argc, char** argv)
{
    // Wrap everything in a try block.  Do this every time,
    // because exceptions will be thrown for problems.
    try {

    // Define the command line object.
    CmdLine cmd("Analog Laser Test tool", ' ', "0.1");

    // Define a value argument and add it to the command line.
    ValueArg<int> updateRate("u","update", "Update rate in milliseconds", false ,100,"string", cmd);
    ValueArg<string> configFile("c","config", "Configuration file", true, "","string", cmd);

    // Parse the args.
    cmd.parse( argc, argv );

    runAnalogLaser(updateRate.getValue(), configFile.getValue());

    } catch (ArgException &e)  // catch any exceptions
    { cerr << "error: " << e.error() << " for arg " << e.argId() << endl; }
}

