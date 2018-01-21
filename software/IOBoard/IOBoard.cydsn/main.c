/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    RED_Write(1);
    GREEN_Write(1);
    BLUE_Write(1);
    
    int state = 0;
    
    VDAC_1_Start();
    VDAC_2_Start();
    
   SPI_Start();
    
    VDAC_1_SetValue(1);
    VDAC_2_SetValue(0);
    
    int dacValue = 0;
    
    int digitalTest = 0;

    uint8_t rxIndex = 0;
    uint8_t txTestData[4] = {0x12, 0x34, 0x45, 0x67};
    uint8_t rxTestData[4];
    
    for(;;)
    {
        /* Place your application code here. */
        CyDelay(100);
        GREEN_Write(!GREEN_Read());
        
        VDAC_1_SetValue(dacValue);
        VDAC_2_SetValue(dacValue);
        dacValue += 10;
        
        if (SPI_SpiUartGetTxBufferSize())
        {
            rxIndex = 0;
            SPI_SpiUartPutArray(txTestData, 4);
        }
        while (SPI_SpiUartGetRxBufferSize() > 0)        
        {
            txTestData[rxIndex++] = SPI_SpiUartReadRxData();
        }
//        switch (state)
//        {
//            case 0:
//                RED_Write(0);
//                state++;
//                break;
//            case 1:
//                RED_Write(1);
//                GREEN_Write(0);
//                break;
//            case 4:
//                BLUE_Write(0);
//                break;
//            case 8:
//                GREEN_Write(1);
//                break;
//            case 12:
//                BLUE_Write(1);
//                break;
//            case 20:
//                state = 0;
//        }        
//        state++;
    }
}

/* [] END OF FILE */
