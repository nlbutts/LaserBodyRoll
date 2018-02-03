#include <string>
#include <iostream>
#include <algorithm>
#include "tclap/CmdLine.h"

extern "C" {
#include "cybtldr_api.h"
#include "cybtldr_api2.h"
}

using namespace TCLAP;
using namespace std;

int openSPI(void)
{
    return CYRET_SUCCESS;
}

int closeSPI()
{
    return CYRET_SUCCESS;

}

int readData(uint8_t *buf, int length)
{
    return CYRET_SUCCESS;

}

int writeData(uint8_t *buf, int length)
{
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

