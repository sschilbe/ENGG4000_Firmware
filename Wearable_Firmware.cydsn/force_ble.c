/**
*
* @file
* force_ble.c
*
* @brief
* Implementation for controlling the Force service
*
* Author: Schilbe, Seth
* Date: 2019 - 12 - 01 
*/

/*------------------------------------------------------------
INCLUDES
------------------------------------------------------------*/
#include "connection_ble.h"
#include "force_ble.h"
#include "force_adc.h"
#include "project.h"
#include <stdio.h>

/*------------------------------------------------------------
LITERAL CONSTANTS
------------------------------------------------------------*/
#define FORCE_DATA_LEN      (16u)
#define IMU_DATA_LEN        (12u)
#define NOTIFICATION_LEN    ( FORCE_DATA_LEN + IMU_DATA_LEN )

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
/* Force data is in a uint8_t array but values are actually uint16_t's */
uint16_t currentNotificationData[NOTIFICATION_LEN/2] = {0};
bool forceNotificationsEnabled = false;

cy_stc_ble_gatt_handle_value_pair_t force_notification = {
    .value.val = currentNotificationData,
    .value.len = NOTIFICATION_LEN,
    .attrHandle = FSR_IMU_DATA_CHAR_HANDLE
};

/*------------------------------------------------------------
PROCEDURES
------------------------------------------------------------*/
void bleForceInit(void)
{
    /* No initialization required currently */
}

void forceSendNotification(void)
{
    cy_stc_ble_conn_handle_t connHandle = getConnection();
    if( forceNotificationsEnabled )
    {
        getForceValues( currentNotificationData );
        if(Cy_BLE_GATT_GetBusyStatus(connHandle.attId) == CY_BLE_STACK_STATE_FREE)
        {
            cy_en_ble_api_result_t result = Cy_BLE_GATTS_SendNotification( &connHandle, &force_notification );           
            if( CY_BLE_SUCCESS != result )
            {
               printf("Error sending characteristic notification: %d\r\n", result);
            }
        } else
        {
            printf("Stack state is not free");
        }
    }
}

/* 
 * Because this is a custom service this callback is manually called
 * when an event with any relevant handles is received
 */
void bleForceCallback(uint32_t event, void *eventParam)
{
    cy_stc_ble_gatts_write_cmd_req_param_t *writeReqParameter = (cy_stc_ble_gatts_write_cmd_req_param_t *)eventParam;
    cy_stc_ble_conn_handle_t connHandle = getConnection();
    cy_en_ble_gatt_err_code_t result;
    
    switch(event)
    {
        case CY_BLE_EVT_GATTS_WRITE_REQ:
            // Check if the write request is for the Force CCCD
            /* Update GATT DB with latest CCCD value */
            if( FSR_IMU_DATA_CONFIG_HANDLE == writeReqParameter->handleValPair.attrHandle )
            {
                if( CY_BLE_GATT_ERR_NONE != ( result = Cy_BLE_GATTS_WriteAttributeValuePeer( &connHandle, &writeReqParameter->handleValPair ) ) )
                {
                    printf("Invalid CCCD write to force_imu, error: %d\r\n", result);
                } else
                {
                    forceNotificationsEnabled = ( writeReqParameter->handleValPair.value.val[0] );
                    if( forceNotificationsEnabled )
                    {
                        printf("Enabled Notifications\r\n");
                    } 
                }
            }
            
            Cy_BLE_GATTS_WriteRsp(writeReqParameter->connHandle);
            break;
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED:
            forceNotificationsEnabled = false;
            printf("Disabled Notifications\r\n");
            break;
            
        default:
            printf("UNHANDLED EVENT FOR FORCE_IMU SERVICE, event id: %d\r\n", event);
            break;
    }
}

/* [] END OF FILE */
