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
#define IMU_SERVICE_HANDLE  CY_BLE_IMU_SERVICE_HANDLE
#define IMU_DECL_HANDLE     CY_BLE_IMU_ACCELERATIONGYROSCOPE_DECL_HANDLE
#define IMU_CHAR_HANDLE     CY_BLE_IMU_ACCELERATIONGYROSCOPE_CHAR_HANDLE
#define IMU_DESC_HANDLE     CY_BLE_IMU_ACCELERATIONGYROSCOPE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE
#define IMU_CONFIG_HANDLE   CY_BLE_IMU_ACCELERATIONGYROSCOPE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE

#define IMU_FIRST_HANDLE    IMU_SERVICE_HANDLE
#define IMU_LAST_HANDLE     IMU_CONFIG_HANDLE

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
void updateImuData( uint8_t newData[] );

#endif /* IMU_BLE_H */
/* [] END OF FILE */
