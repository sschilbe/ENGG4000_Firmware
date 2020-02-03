/**
*
* @file
* force_ble.h
*
* @brief
* Interface for controlling the Force service
*
* Author: Schilbe, Seth
* Date: 2019 - 12 - 01 
*/

#ifndef FORCE_BLE_H
#define FORCE_BLE_H
    
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
#define FSR_IMU_SERVICE_HANDLE     CY_BLE_FSR_IMU_SERVICE_HANDLE
#define FSR_IMU_DATA_DECL_HANDLE   CY_BLE_FSR_IMU_DATA_DECL_HANDLE
#define FSR_IMU_DATA_CHAR_HANDLE   CY_BLE_FSR_IMU_DATA_CHAR_HANDLE
#define FSR_IMU_DATA_CONFIG_HANDLE CY_BLE_FSR_IMU_DATA_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE
#define FSR_IMU_DATA_DESC_HANDLE   CY_BLE_FSR_IMU_DATA_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE

#define FSR_IMU_FIRST_HANDLE    FSR_IMU_SERVICE_HANDLE
#define FSR_IMU_LAST_HANDLE     FSR_IMU_DATA_DESC_HANDLE

/*------------------------------------------------------------
MEMORY CONSTANTS
------------------------------------------------------------*/

/*------------------------------------------------------------
VARIABLES
------------------------------------------------------------*/

/*------------------------------------------------------------
PROTOTYPES
------------------------------------------------------------*/
void bleForceInit(void);
void bleForceCallback(uint32_t event, void *eventParam);
void forceSendNotification(void);

#endif /* FORCE_BLE_H */

/* [] END OF FILE */
