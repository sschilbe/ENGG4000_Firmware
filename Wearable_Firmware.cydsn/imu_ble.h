/**
*
* @file
* imu_ble.h
*
* @brief
* Interface for controlling the IMU service
*
* Author: Schilbe, Seth
* Date: 2019 - 12 - 01 
*/

#ifndef IMU_BLE_H
#define IMU_BLE_H
    
/*------------------------------------------------------------
INCLUDES
------------------------------------------------------------*/
#include "project.h"

/*------------------------------------------------------------
LITERAL CONSTANTS
------------------------------------------------------------*/

/*------------------------------------------------------------
MACROS
------------------------------------------------------------*/

/*------------------------------------------------------------
TYPES
------------------------------------------------------------*/

/* Re-define macros for accessing IMU service to improve readability */
#define IMU_SERVICE_HANDLE      CY_BLE_IMU_SERVICE_HANDLE
#define IMU_ACCEL_DECL_HANDLE   CY_BLE_IMU_ACCELERATION_DECL_HANDLE
#define IMU_ACCEL_CHAR_HANDLE   CY_BLE_IMU_ACCELERATION_CHAR_HANDLE
#define IMU_ACCEL_DESC_HANDLE   CY_BLE_IMU_ACCELERATION_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE
#define IMU_ACCEL_CONFIG_HANDLE CY_BLE_IMU_ACCELERATION_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE
#define IMU_GYRO_DECL_HANDLE    CY_BLE_IMU_GYROSCOPE_DECL_HANDLE
#define IMU_GYRO_CHAR_HANDLE    CY_BLE_IMU_GYROSCOPE_CHAR_HANDLE
#define IMU_GYRO_DESC_HANDLE    CY_BLE_IMU_GYROSCOPE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE
#define IMU_GYRO_CONFIG_HANDLE  CY_BLE_IMU_GYROSCOPE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE

#define IMU_FIRST_HANDLE    IMU_SERVICE_HANDLE
#define IMU_LAST_HANDLE     IMU_GYRO_CONFIG_HANDLE

/*------------------------------------------------------------
MEMORY CONSTANTS
------------------------------------------------------------*/

/*------------------------------------------------------------
VARIABLES
------------------------------------------------------------*/

/*------------------------------------------------------------
PROTOTYPES
------------------------------------------------------------*/
void bleImuInit(void);
void bleImuCallback(uint32_t event, void *eventParam);
void imuSendNotification();

#endif /* IMU_BLE_H */
/* [] END OF FILE */
