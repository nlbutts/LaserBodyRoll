/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*  BLE example project that measures the battery voltage using PSoC 4 BLE's
*  internal ADC and notifies the BLE central device on any change in battery
*  voltage.
*
* Note:
*
* Hardware Dependency:
*  CY8CKIT-042 BLE
*
********************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "common.h"
#include "ble_protocol.h"

uint32_t _oneSecondTimer = 0;

uint8_t _laserNotify[2] = {0};
CYBLE_GATT_HANDLE_VALUE_PAIR_T _laserNotificationCCDHandle;

uint8_t programData[100];
uint32_t programDataLength;

/*******************************************************************************
* Function Name: AppCallBack()
********************************************************************************
*
* Summary:
*   This is an event callback function to receive events from the BLE Component.
*
*  event - the event code
*  *eventParam - the event parameters
*
* Return:
*   None
*
*******************************************************************************/
void AppCallBack(uint32 event, void* eventParam)
{
    CYBLE_API_RESULT_T apiResult;
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
    CYBLE_GAP_BD_ADDR_T localAddr;
    uint8 i;

    switch (event)
	{
        /**********************************************************
        *                       General Events
        ***********************************************************/
		case CYBLE_EVT_STACK_ON: /* This event is received when the component is Started */
            /* Enter into discoverable mode so that remote can search it. */
            apiResult = CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            if(apiResult != CYBLE_ERROR_OK)
            {
                DBG_PRINTF("StartAdvertisement API Error: %d \r\n", apiResult);
                ShowError();
            }
            DBG_PRINTF("Bluetooth On, StartAdvertisement with addr: ");
            localAddr.type = 0u;
            CyBle_GetDeviceAddress(&localAddr);
            for(i = CYBLE_GAP_BD_ADDR_SIZE; i > 0u; i--)
            {
                DBG_PRINTF("%2.2x", localAddr.bdAddr[i-1]);
            }
            DBG_PRINTF("\r\n");
            break;
		case CYBLE_EVT_TIMEOUT:
			break;
		case CYBLE_EVT_HARDWARE_ERROR:    /* This event indicates that some internal HW error has occurred. */
            DBG_PRINTF("Hardware Error \r\n");
            ShowError();
			break;
        case CYBLE_EVT_HCI_STATUS:
            DBG_PRINTF("CYBLE_EVT_HCI_STATUS: %x \r\n", *(uint8 *)eventParam);
            ShowError();
			break;

        /**********************************************************
        *                       GAP Events
        ***********************************************************/
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            DBG_PRINTF("CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP, state: %x\r\n", CyBle_GetState());
            if(CYBLE_STATE_DISCONNECTED == CyBle_GetState())
            {
                /* Fast and slow advertising period complete, go to low power
                 * mode (Hibernate mode) and wait for an external
                 * user event to wake up the device again */
                DBG_PRINTF("Hibernate \r\n");
                Advertising_LED_Write(LED_OFF);
                Disconnect_LED_Write(LED_ON);
            #if (DEBUG_UART_ENABLED == ENABLED)
                while((UART_DEB_SpiUartGetTxBufferSize() + UART_DEB_GET_TX_FIFO_SR_VALID) != 0);
            #endif /* (DEBUG_UART_ENABLED == ENABLED) */
                CySysPmHibernate();
            }
            break;
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            DBG_PRINTF("CYBLE_EVT_GAP_DEVICE_CONNECTED: %d \r\n", *(uint8 *)eventParam);
            Advertising_LED_Write(LED_OFF);
            break;
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            DBG_PRINTF("CYBLE_EVT_GAP_DEVICE_DISCONNECTED\r\n");
            /* Put the device into discoverable mode so that a remote can search it. */
            apiResult = CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            if(apiResult != CYBLE_ERROR_OK)
            {
                DBG_PRINTF("StartAdvertisement API Error: %d \r\n", apiResult);
                ShowError();
            }
            break;

        /**********************************************************
        *                       GATT Events
        ***********************************************************/
        case CYBLE_EVT_GATT_CONNECT_IND:
            DBG_PRINTF("CYBLE_EVT_GATT_CONNECT_IND: %x, %x \r\n",
                (*(CYBLE_CONN_HANDLE_T *)eventParam).attId,
                (*(CYBLE_CONN_HANDLE_T *)eventParam).bdHandle);
            break;
        case CYBLE_EVT_GATT_DISCONNECT_IND:
            DBG_PRINTF("CYBLE_EVT_GATT_DISCONNECT_IND \r\n");
            break;

        case CYBLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ:
            /* Triggered on server side when client sends read request and when
            * characteristic has CYBLE_GATT_DB_ATTR_CHAR_VAL_RD_EVENT property set.
            * This event could be ignored by application unless it need to response
            * by error response which needs to be set in gattErrorCode field of
            * event parameter. */
            DBG_PRINTF("CYBLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ: handle: %x \r\n",
                ((CYBLE_GATTS_CHAR_VAL_READ_REQ_T *)eventParam)->attrHandle);
            break;

        case CYBLE_EVT_GATTS_WRITE_REQ:
            DBG_PRINTF("CYBLE_EVT_GATTS_WRITE_REQ\n");
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;

            if(wrReqParam->handleValPair.attrHandle == CYBLE_LAVA_LASERDISTANCE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE)
            {
                /* only update the value and write the response if the requested write is allowed */
                if(wrReqParam->handleValPair.value.val[CYBLE_LAVA_LASERDISTANCE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX] == 1)
                {
                    _laserNotify[0] = 1;
                }
                else
                {
                    _laserNotify[0] = 1;
                }

                /* Update CCCD handle with notification status data*/
                _laserNotificationCCDHandle.attrHandle = CYBLE_LAVA_LASERDISTANCE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE;
                _laserNotificationCCDHandle.value.val  = _laserNotify;
                _laserNotificationCCDHandle.value.len  = 2;

                /* Report data to BLE component for sending data when read by Central device */
                CyBle_GattsWriteAttributeValue(&_laserNotificationCCDHandle, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
            }
            /* Write request for time/date */
            if(wrReqParam->handleValPair.attrHandle == CYBLE_LAVA_PROGRAM_CHAR_HANDLE)
            {
                programDataLength = wrReqParam->handleValPair.value.len;
                memcpy(programData, wrReqParam->handleValPair.value.val, programDataLength);
                /* only update the value and write the response if the requested write is allowed */
//                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
//                {
//                    int len = wrReqParam->handleValPair.value.len;
//                    int data = wrReqParam->handleValPair.value.val[0];
//                }
            }


            CyBle_GattsWriteRsp(cyBle_connHandle);
            break;




        /**********************************************************
        *                       Other Events
        ***********************************************************/
        case CYBLE_EVT_PENDING_FLASH_WRITE:
            /* Inform application that flash write is pending. Stack internal data
            * structures are modified and require to be stored in Flash using
            * CyBle_StoreBondingData() */
            DBG_PRINTF("CYBLE_EVT_PENDING_FLASH_WRITE\r\n");
            break;

        default:
            DBG_PRINTF("OTHER event: %lx \r\n", event);
			break;
	}
}

CY_ISR(timerISR)
{
    RED_LED_Write(!RED_LED_Read());
    _oneSecondTimer++;
    Timer1_ClearInterrupt(Timer1_INTR_MASK_TC);
}

void HandleLeds()
{
    static uint32 ledTimer = 0;

   /* Blink blue LED to indicate that device advertises */
    if(CyBle_GetState() == CYBLE_STATE_ADVERTISING)
    {
        uint32_t now = _oneSecondTimer;
        if(now != ledTimer)
        {
            ledTimer = now;
            Advertising_LED_Write(!Advertising_LED_Read());
        }
    }
}


void from_main(uint8_t * buf, uint32_t len)
{
    CYBLE_GATTS_HANDLE_VALUE_NTF_T  tempHandle;

    if (len == 5)
    {
        Disconnect_LED_Write(!Disconnect_LED_Read());
        //Advertising_LED_Write(!Advertising_LED_Read());
        if (CyBle_GetState() == CYBLE_STATE_CONNECTED)
        {
    		/* Update notification data*/
            tempHandle.attrHandle = CYBLE_LAVA_LASERDISTANCE_CHAR_HANDLE;
            tempHandle.value.val = (uint8_t*)(buf + 1);
            tempHandle.value.len = 4;
    		/* Send the updated handle as part of attribute for notifications */
            CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED );
            if (_laserNotify[0])
            {
    		    CyBle_GattsNotification(cyBle_connHandle, &tempHandle);
            }
        }
	}
}

int main()
{
    CYBLE_API_RESULT_T apiResult;

    CyGlobalIntEnable;

    //CySysTickEnable();

    Disconnect_LED_Write(LED_OFF);
    Advertising_LED_Write(LED_OFF);

    CyBle_Start(AppCallBack);

    timerISR_StartEx(timerISR);
    Timer1_Start();
    Timer1_SetInterruptMode(Timer1_INTR_MASK_TC);
    Timer1_WritePeriod(32768);

    SPI_Start();

    BLEProtocol protocol;
    ble_protocol_init(&protocol);
    ble_protocol_registerCallback(&protocol, TO_BLE_DEV, from_main);

	while(1)
    {
        HandleLeds();

        uint8_t rxBytes = SPI_SpiUartGetRxBufferSize();
        while (rxBytes--)
        {
            uint8_t data = SPI_SpiUartReadRxData();
            ble_protocol_push_msg(&protocol, &data, 1);
            ble_protocol_parse(&protocol);
        }

        if (programDataLength > 0)
        {
            uint8_t packet[100];
            int txPacketLen;
            CyGlobalIntDisable;
            txPacketLen = ble_protocol_generatePacket(packet,
                                                      100,
                                                      0,
                                                      FROM_BLE_DEV,
                                                      programData,
                                                      programDataLength);
            SPI_SpiUartPutArray(packet, txPacketLen);
            programDataLength = 0;
            CyGlobalIntEnable;
        }

#if 1
        /* Process all the generated events. */
        CyBle_ProcessEvents();

        /***********************************************************************
        * Wait for connection established with Central device
        ***********************************************************************/
        if(CyBle_GetState() == CYBLE_STATE_CONNECTED)
        {
            /*******************************************************************
            *  Periodically simulate Battery level charging.
            *******************************************************************/
            //SimulateBattery();
            CyBle_ProcessEvents();

            //MeasureBattery();
        }
#endif
	}
}


/* [] END OF FILE */

