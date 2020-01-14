/**
*
* @file
* imu_ble.c
*
* @brief
* Implementation for controlling the IMU service
*
* Author: Schilbe, Seth
* Date: 2019 - 12 - 01 
*/

/*------------------------------------------------------------
INCLUDES
------------------------------------------------------------*/
#include "connection_ble.h"
#include "imu_ble.h"
#include <stdio.h>

/*------------------------------------------------------------
LITERAL CONSTANTS
------------------------------------------------------------*/
#define IMU_NOTIFICATION_LEN  (12u)

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
/* IMU data is in the format of:
 * First 6 bytes, accel data (x,y,z)
 * Next  6 bytes, gyro data (x,y,z) 
 * IMU data is stored in a uint8_t array but readings are uint16_t's
 */
uint8_t currentIMUData[IMU_NOTIFICATION_LEN] = {0};
bool imuNotificationsEnabled = false;

/*------------------------------------------------------------
PROCEDURES
------------------------------------------------------------*/
void bleImuInit(void)
{
    /* No initialization required currently */
}

void updateImuData( uint8_t newData[] )
{
    memcpy( currentIMUData, newData, sizeof( uint8_t ) * IMU_NOTIFICATION_LEN );
}

/*
 * Because this is a custom service this callback is manually called
 * when an event with any relevant handles is received
 */
void imuSendNotification()
{
    cy_stc_ble_conn_handle_t connHandle = getConnection();
    if( imuNotificationsEnabled )
    {
        currentIMUData[0]++;
        cy_stc_ble_gatt_handle_value_pair_t accel_notification = {
            .value.val = currentIMUData,
            .value.len = IMU_NOTIFICATION_LEN,
            .attrHandle = IMU_CHAR_HANDLE
        };
        
        cy_en_ble_api_result_t result = Cy_BLE_GATTS_SendNotification( &connHandle, &accel_notification );
        if( CY_BLE_SUCCESS != result )
        {
           printf("Error sending imu characteristic: %d\r\n", result);
        }
    }
}

void bleImuCallback(uint32_t event, void *eventParam)
{
    cy_stc_ble_gatts_write_cmd_req_param_t *writeReqParameter = (cy_stc_ble_gatts_write_cmd_req_param_t *)eventParam;
    cy_stc_ble_conn_handle_t connHandle = getConnection();
    cy_en_ble_gatt_err_code_t result;
    
    switch(event)
    {
        case CY_BLE_EVT_GATTS_WRITE_REQ:
            // Check if the write request is for the Acceleration CCCD
            /* Update GATT DB with latest CCCD value */
            if( IMU_CONFIG_HANDLE == writeReqParameter->handleValPair.attrHandle )
            {
                if( CY_BLE_GATT_ERR_NONE != ( result = Cy_BLE_GATTS_WriteAttributeValuePeer( &connHandle, &writeReqParameter->handleValPair ) ) )
                {
                    printf("Invalid CCCD write to imu, error: %d\r\n", result);
                } else
                {
                    imuNotificationsEnabled = ( writeReqParameter->handleValPair.value.val[0] );
                }
            }
            Cy_BLE_GATTS_WriteRsp(writeReqParameter->connHandle);
            break;    
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED:
            imuNotificationsEnabled = false;
            break;
            
        default:
            printf("UNHANDLED EVENT FOR IMU SERVICE, event id: %d", event);
            break;
    }
}

/* [] END OF FILE */
