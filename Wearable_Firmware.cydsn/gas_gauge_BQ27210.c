/**
*
* @file
* gas_gauge_BQ27210.c
*
* @brief
* Implementation for controlling the Gas Gauge over I2C
*
* Author: Schilbe, Seth
*Date: 2019 - 02 - 22 */

/*------------------------------------------------------------
INCLUDES
------------------------------------------------------------*/
#include "project.h"
#include "gas_gauge_BQ27210.h"
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
static bool readRegister(uint8_t* output, uint8_t offset);
static bool writeRegister(uint8_t offset, uint8_t data);
static bool readRegisterRegion(uint8_t* output, uint8_t offset, uint8_t length);

//Reads two 8-bit regs, LSByte then MSByte order, and concatenates them.
//  Acts as a 16-bit read operation
static bool readRegisterInt16(int16_t* output, uint8_t offset);

bool gasGaugeInit()
{
    // Undetermined what needs to be initialized
    
    return true;
}

void gasGaugeConfigure()
{
    // Undetermined what needs to be configured
}

bool readRegister(uint8_t* output, uint8_t offset)
{
    cy_en_scb_i2c_status_t status;
    if( ( status = I2C_MasterSendStart(BQ27210_DEVICE_ADDRESS, CY_SCB_I2C_WRITE_XFER , TIMEOUT) ) != CY_SCB_I2C_SUCCESS) {
        printf("Error starting communication: %x\r\n", status);
    }
    
    /* Set to read from buffer at offset */
    I2C_MasterWriteByte( offset, TIMEOUT );

    /* Restart */
    I2C_MasterSendReStart(BQ27210_DEVICE_ADDRESS, CY_SCB_I2C_READ_XFER, TIMEOUT);
    
    /* Read single byte */
    I2C_MasterReadByte(CY_SCB_I2C_NAK, output, TIMEOUT); // Read from register
    
    I2C_MasterSendStop(TIMEOUT); 

    return true;
}

bool readRegisterInt16(int16_t* output, uint8_t offset )
{
    uint8_t localBuffer[2];
    readRegisterRegion(localBuffer, offset, 2);
    *output = (int16_t)( localBuffer[0] | (localBuffer[1] << 8));
    
    return true;
}

bool writeRegister(uint8_t offset, uint8_t data)
{
    I2C_MasterSendStart(BQ27210_DEVICE_ADDRESS, CY_SCB_I2C_WRITE_XFER , TIMEOUT);
    
    /* Set to read from buffer at offset */
    I2C_MasterWriteByte( offset, TIMEOUT );
    
    /* Set to write data to offset */
    I2C_MasterWriteByte( data, TIMEOUT );
    
    I2C_MasterSendStop(TIMEOUT);
    
    return true;
}

static bool readRegisterRegion(uint8_t* output, uint8_t offset, uint8_t length)
{    
    I2C_MasterSendStart(BQ27210_DEVICE_ADDRESS, CY_SCB_I2C_WRITE_XFER , TIMEOUT);
    
    /* Set to read from buffer at offset */
    I2C_MasterWriteByte( offset, TIMEOUT );
    
    /* Restart */
    I2C_MasterSendReStart(BQ27210_DEVICE_ADDRESS, CY_SCB_I2C_READ_XFER, TIMEOUT);
    
    /* Read specified number of bytes */
    for( uint8_t i = 0; i < length - 1; i++ )
    {
        I2C_MasterReadByte(CY_SCB_I2C_ACK, &(output[i]), TIMEOUT);
    }
    
    // Nack the last value to be read
    I2C_MasterReadByte(CY_SCB_I2C_NAK, &(output[length-1]), TIMEOUT);
    
    I2C_MasterSendStop(TIMEOUT); 

    return true;
}

/* [] END OF FILE */
