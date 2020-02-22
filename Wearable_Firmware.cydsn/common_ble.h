/**
*
* @file
* common_ble.h
*
* @brief
* Interface for controlling common BLE functionality
*
* Author: Schilbe, Seth
* Date: 2019 - 12 - 01 
*/

#ifndef COMMON_BLE_H
#define COMMON_BLE_H

/*------------------------------------------------------------
INCLUDES
------------------------------------------------------------*/
#include <project.h>

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
PROTOTYPES
------------------------------------------------------------*/
void BleInit(void);
void BleCallback(uint32_t event, void *eventParam);

void sendNotifications(void);
#endif /* COMMON_BLE_H */
/* [] END OF FILE */
