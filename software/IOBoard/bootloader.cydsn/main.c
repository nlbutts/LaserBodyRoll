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
    
    for (int i = 0; i < 5; i++)
    {
        RED_Write(0);
        CyDelay(100);
        RED_Write(1);
        CyDelay(100);
    }
    RED_Write(0);
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Bootloader_Start();
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
