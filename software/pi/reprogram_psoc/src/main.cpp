#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
#include "tclap/CmdLine.h"
#include "reprogram_logic.h"

using namespace TCLAP;
using namespace std;

int main(int argc, char** argv)
{
    // Wrap everything in a try block.  Do this every time,
    // because exceptions will be thrown for problems.
    try {

    // Define the command line object.
    CmdLine cmd("PSoC Reprogramming tool", ' ', "0.1");

    // Define a value argument and add it to the command line.
    ValueArg<string> inputFile("i","input", "Application programming image", true,"","string", cmd);

    // Define a switch and add it to the command line.
    // SwitchArg reverseSwitch("r","reverse","Print name backwards", false);
    // cmd.add( reverseSwitch );

    // Parse the args.
    cmd.parse( argc, argv );

    programPsoC(inputFile.getValue());

    } catch (ArgException &e)  // catch any exceptions
    { cerr << "error: " << e.error() << " for arg " << e.argId() << endl; }
}

