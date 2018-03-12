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
    PWM_GREEN_Start();

    CyBle_ProcessEvents();


    
    for(;;)
    {
        CyBle_ProcessEvents();
        /* Place your application code here. */
        BLUE_LED_Write(0);
        CyDelay(1000);
        BLUE_LED_Write(1);
        CyDelay(1000);
    }
}

/* [] END OF FILE */
