/**
*
* @file
* force_adc.h
*
* @brief
* Interface for controlling the ADC peripheral for Force data
*
* Author: Schilbe, Seth
* Date: 2019 - 01 - 10 
*/

#ifndef FORCE_ADC_H
#define FORCE_ADC_H
    
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

/*------------------------------------------------------------
MEMORY CONSTANTS
------------------------------------------------------------*/

/*------------------------------------------------------------
VARIABLES
------------------------------------------------------------*/

/*------------------------------------------------------------
PROTOTYPES
------------------------------------------------------------*/
void adcInit();
void getForceValues( uint16_t values[] );

#endif
/* [] END OF FILE */
