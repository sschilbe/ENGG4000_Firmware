/**
*
* @file
* common_ble.c
*
* @brief
* Implementation for controlling common BLE functionality
*
* Author: Schilbe, Seth
* Date: 2019 - 12 - 01 
*/

/*------------------------------------------------------------
INCLUDES
------------------------------------------------------------*/
#include "common_ble.h"
#include "connection_ble.h"
#include "force_ble.h"
#include "imu_ble.h"
#include "project.h"
#include <stdio.h>

/*------------------------------------------------------------
LITERAL CONSTANTS
------------------------------------------------------------*/

/*------------------------------------------------------------
MACROS
------------------------------------------------------------*/

/*------------------------------------------------------------
TYPES
------------------------------------------------------------*/

/*------------------------------------------------------------
MEMORY CONSTANTS
------------------------------------------------------------*/

/*------------------------------------------------------------
VARIABLES
------------------------------------------------------------*/

/*------------------------------------------------------------
PROCEDURES
------------------------------------------------------------*/
void sendNotifications(void)
{
    /* Tell each service to send notification */
    imuSendNotification();
    forceSendNotification();
}

void TimerInterruptHandler(void)
{
    /* Clear the interrupt flag */
    Cy_TCPWM_ClearInterrupt(Timer_HW, Timer_CNT_NUM, CY_TCPWM_INT_ON_TC);
    
    sendNotifications();
}

void BleInit(void)
{
    Cy_BLE_Start(BleCallback);
    while(Cy_BLE_GetState() != CY_BLE_STATE_ON) // Get the stack going
    {
        Cy_BLE_ProcessEvents();
    }
    
    bleImuInit();
    bleForceInit();
}

void BleCallback(uint32_t event, void *eventParam)
{
    cy_ble_gatt_db_attr_handle_t attribute_handle;
    cy_stc_ble_gap_conn_param_updated_in_controller_t* connection_update_event;
    
    /* Take an action based on the current event */
    switch (event)
    {
        /* This event is received when the BLE stack is Started */
        case CY_BLE_EVT_STACK_ON:
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED:
            bleImuCallback( event, eventParam );
            bleForceCallback( event, eventParam );
            
            PWM_RED_BLINK_Start();
            Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
            Cy_TCPWM_TriggerReloadOrIndex(PWM_GREEN_BLINK_HW,PWM_GREEN_BLINK_CNT_NUM);
            Cy_TCPWM_PWM_Disable(PWM_GREEN_BLINK_HW,PWM_GREEN_BLINK_CNT_NUM);
            break;

        case CY_BLE_EVT_GATT_CONNECT_IND:
            Cy_TCPWM_TriggerReloadOrIndex(PWM_RED_BLINK_HW,PWM_RED_BLINK_CNT_NUM);
            Cy_TCPWM_PWM_Disable(PWM_RED_BLINK_HW,PWM_RED_BLINK_CNT_NUM);     
            PWM_GREEN_BLINK_Start();
            
            // Save connection handle
            setConnection( *(cy_stc_ble_conn_handle_t*)eventParam );
            break;
        
        case CY_BLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE:
            connection_update_event = (cy_stc_ble_gap_conn_param_updated_in_controller_t *)eventParam;
            printf("Connection updated, interval: %x\r\n", connection_update_event->connIntv);
            break;
        
        case CY_BLE_EVT_GATTS_WRITE_REQ:
            /* Forward the write to the corresponding service */
            attribute_handle = ((cy_stc_ble_gatts_write_cmd_req_param_t *)eventParam)->handleValPair.attrHandle;
            if( IMU_FIRST_HANDLE <= attribute_handle && IMU_LAST_HANDLE >= attribute_handle )
            {
                bleImuCallback( event, eventParam );
            } else if( FSR_FIRST_HANDLE <= attribute_handle && FSR_LAST_HANDLE >= attribute_handle )
            {
                bleForceCallback( event, eventParam );
            } else
            {
                printf("INVALID HANDLE FOR WRITE");
            }
            break;
        
        default:
            break;
    }
}

/* [] END OF FILE */
