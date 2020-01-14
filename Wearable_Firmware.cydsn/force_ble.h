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
#define FSR_SERVICE_HANDLE      CY_BLE_FSR_SERVICE_HANDLE
#define FSR_FORCE_DECL_HANDLE   CY_BLE_FSR_FORCE_DECL_HANDLE
#define FSR_FORCE_CHAR_HANDLE   CY_BLE_FSR_FORCE_CHAR_HANDLE
#define FSR_FORCE_CONFIG_HANDLE CY_BLE_FSR_FORCE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE
#define FSR_FORCE_DESC_HANDLE   CY_BLE_FSR_FORCE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE

#define FSR_FIRST_HANDLE    FSR_SERVICE_HANDLE
#define FSR_LAST_HANDLE     FSR_FORCE_DESC_HANDLE

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
void updateForceData( uint8_t newData[] );

#endif /* FORCE_BLE_H */

/* [] END OF FILE */
