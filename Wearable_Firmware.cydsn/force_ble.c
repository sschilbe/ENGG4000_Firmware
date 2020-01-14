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
#define FORCE_NOTIFICATION_LEN  (16u)

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
uint8_t currentForceData[FORCE_NOTIFICATION_LEN] = {0};
bool forceNotificationsEnabled = false;

/*------------------------------------------------------------
PROCEDURES
------------------------------------------------------------*/
void bleForceInit(void)
{
    /* No initialization required currently */
}

void updateForceData( uint8_t newData[] )
{
    memcpy( currentForceData, newData, sizeof( uint8_t ) * FORCE_NOTIFICATION_LEN );   
}

void forceSendNotification(void)
{
    cy_stc_ble_conn_handle_t connHandle = getConnection();
    if( forceNotificationsEnabled )
    {
        getForceValues( currentForceData );
        for( uint8 i = 0; i < 8; i++ ) {
            printf("Current Force Data: %d\r\n", currentForceData[i]);
        }
        
        cy_stc_ble_gatt_handle_value_pair_t force_notification = {
            .value.val = currentForceData,
            .value.len = FORCE_NOTIFICATION_LEN,
            .attrHandle = FSR_FORCE_CHAR_HANDLE
        };
        
        cy_en_ble_api_result_t result = Cy_BLE_GATTS_SendNotification( &connHandle, &force_notification );
        if( CY_BLE_SUCCESS != result )
        {
           printf("Error sending force characteristic: %d\r\n", result);
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
            if( FSR_FORCE_CONFIG_HANDLE == writeReqParameter->handleValPair.attrHandle )
            {
                if( CY_BLE_GATT_ERR_NONE != ( result = Cy_BLE_GATTS_WriteAttributeValuePeer( &connHandle, &writeReqParameter->handleValPair ) ) )
                {
                    printf("Invalid CCCD write to force, error: %d\r\n", result);
                } else
                {
                    forceNotificationsEnabled = ( writeReqParameter->handleValPair.value.val[0] );
                }
            }
            
            Cy_BLE_GATTS_WriteRsp(writeReqParameter->connHandle);
            break;
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED:
            forceNotificationsEnabled = false;
            break;
            
        default:
            printf("UNHANDLED EVENT FOR FORCE SERVICE, event id: %d\r\n", event);
            break;
    }
}

/* [] END OF FILE */
