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
    
    VDAC_1_SetValue(1);
    VDAC_2_SetValue(0);
    
    int dacValue = 0;
    
    int digitalTest = 0;
    
    for(;;)
    {
        /* Place your application code here. */
        CyDelay(100);
        VDAC_1_SetValue(dacValue);
        VDAC_2_SetValue(dacValue);
        dacValue += 10;
        
        digitalTest++;
        if (digitalTest > 50)
        {
            digitalTest = 0;
            DIGITAL_OUT1_Write(!DIGITAL_OUT1_Read());
            DIGITAL_OUT2_Write(!DIGITAL_OUT2_Read());
        }
        
        if (DIGITAL_IN1_Read() > 0)
        {
            RED_Write(0);
        }
        else
        {
            RED_Write(1);
        }

        if (DIGITAL_IN2_Read() > 0)
        {
            GREEN_Write(0);
        }
        else
        {
            GREEN_Write(1);
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
