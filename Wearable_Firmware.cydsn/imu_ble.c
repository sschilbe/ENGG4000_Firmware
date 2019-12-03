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
#define ACCEL_NOTIFICATION_LEN  (20u)
#define GYRO_NOTIFICATION_LEN   (20u)

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
uint8_t currentAccelData[ACCEL_NOTIFICATION_LEN] = {0};
uint8_t currentGyroData[GYRO_NOTIFICATION_LEN] = {0};

bool accelNotificationsEnabled = false;
bool gyroNotificationsEnabled = false;
/*------------------------------------------------------------
PROCEDURES
------------------------------------------------------------*/
void bleImuInit(void)
{
    /* No initialization required currently */
}

/* 
 * Because this is a custom service this callback is manually called
 * when an event with any relevant handles is received
 */
void imuSendNotification()
{
    cy_stc_ble_conn_handle_t connHandle = getConnection();
    if( accelNotificationsEnabled )
    {
        printf("Sending Accel Notification\r\n");
        currentAccelData[0]++;
        cy_stc_ble_gatt_handle_value_pair_t accel_notification = {
            .value.val = currentAccelData,
            .value.len = ACCEL_NOTIFICATION_LEN,
            .attrHandle = IMU_ACCEL_CHAR_HANDLE
        };
        
        cy_en_ble_api_result_t result = Cy_BLE_GATTS_SendNotification( &connHandle, &accel_notification );
        if( CY_BLE_SUCCESS != result )
        {
           printf("Error sending acceleration characteristic: %d\r\n", result);
        }
    }
    
    if( gyroNotificationsEnabled )
    {
        printf("Sending Gyro Notification\r\n");
        currentGyroData[0]++;
        cy_stc_ble_gatt_handle_value_pair_t gyro_notification = {
            .value.val = currentGyroData,
            .value.len = GYRO_NOTIFICATION_LEN,
            .attrHandle = IMU_GYRO_CHAR_HANDLE
        };
        
        cy_en_ble_api_result_t result = Cy_BLE_GATTS_SendNotification( &connHandle, &gyro_notification );
        if( CY_BLE_SUCCESS != result )
        {
           printf("Error sending gyroscope characteristic: %d\r\n", result);
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
            if( IMU_ACCEL_CONFIG_HANDLE == writeReqParameter->handleValPair.attrHandle )
            {
                if( CY_BLE_GATT_ERR_NONE != ( result = Cy_BLE_GATTS_WriteAttributeValuePeer( &connHandle, &writeReqParameter->handleValPair ) ) )
                {
                    printf("Invalid CCCD write to gyro, error: %d\r\n", result);
                } else
                {
                    accelNotificationsEnabled = ( writeReqParameter->handleValPair.value.val[0] );
                }
            } else if( IMU_GYRO_CONFIG_HANDLE == writeReqParameter->handleValPair.attrHandle )
            {
                if( CY_BLE_GATT_ERR_NONE != ( result = Cy_BLE_GATTS_WriteAttributeValuePeer( &connHandle, &writeReqParameter->handleValPair ) ) )
                {
                    printf("Invalid CCCD write to gyro, error: %d\r\n", result);
                } else
                {
                    gyroNotificationsEnabled = ( writeReqParameter->handleValPair.value.val[0] );
                }
            }
            
            Cy_BLE_GATTS_WriteRsp(writeReqParameter->connHandle);
            break;
        default:
            printf("UNHANDLED EVENT FOR IMU SERVICE");
            break;
    }
}

/* [] END OF FILE */
