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
#include <project.h>

int main()
{
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    //SPI_Start();

    CyBle_ProcessEvents();

    volatile uint32_t rxBufSize;
    volatile uint32_t txBufSize;
    
    
    for(;;)
    {
        //rxBufSize = SPI_SpiUartGetRxBufferSize();        
        //txBufSize = SPI_SpiUartGetTxBufferSize();
        //if (rxBufSize > 0)
        //{
            //SPI_SpiUartWriteTxData(SPI_SpiUartReadRxData());
        //}
        
        CyBle_ProcessEvents();        
        /* Place your application code here. */
        //BLUE_LED_Write(0);
        //CyDelay(1000);
        //BLUE_LED_Write(1);
        //CyDelay(1000);

        
        BLUE_LED_Write(SCLK_Read());
        GREEN_LED_Write(MOSI_Read());
        RED_LED_Write(MISO_Read());
    }
}

/* [] END OF FILE */
