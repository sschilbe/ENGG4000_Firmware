/**
*
* @file
* imu_i2c.c
*
* @brief
* Implementation for controlling the I2C peripheral for IMU data
*
* Author: Schilbe, Seth
* Date: 2019 - 01 - 10 */

/*------------------------------------------------------------
INCLUDES
------------------------------------------------------------*/
#include "common_i2c.h"
#include <stdio.h>

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
PROCEDURES
------------------------------------------------------------*/
void i2cInit()
{
    cy_en_scb_i2c_status_t initStatus = Cy_SCB_I2C_Init(I2C_HW, &I2C_config, &I2C_context);
    if(initStatus != CY_SCB_I2C_SUCCESS)
    {
        printf("Error initializing I2C interface");
        return;
    }    
    
    uint32_t dataRateSet = Cy_SCB_I2C_SetDataRate(I2C_HW, I2C_DATA_RATE_HZ, I2C_CLK_FREQ_HZ);
    /* check whether data rate set is not greather then required reate. */
    if( dataRateSet > I2C_DATA_RATE_HZ )
    {
        printf("Error configuring data rate for I2C interface");
    }
    
    /* Enable I2C master hardware. */
    Cy_SCB_I2C_Enable(I2C_HW);
}

/* [] END OF FILE */
