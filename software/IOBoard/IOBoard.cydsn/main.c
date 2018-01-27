#include "project.h"
#include "protocol.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    RED_Write(1);
    GREEN_Write(1);
    BLUE_Write(1);

    VDAC_1_Start();
    VDAC_2_Start();

    SPI_Start();

    VDAC_1_SetValue(1);
    VDAC_2_SetValue(0);

    int dacValue = 0;

    for(;;)
    {
        /* Place your application code here. */
        CyDelay(100);
        //GREEN_Write(!GREEN_Read());
        GREEN_Write(1);
        RED_Write(1);

        VDAC_1_SetValue(dacValue);
        VDAC_2_SetValue(dacValue);
        dacValue += 10;

        protocol_process();
        protocol_pushPacket();
    }
}

/* [] END OF FILE */
