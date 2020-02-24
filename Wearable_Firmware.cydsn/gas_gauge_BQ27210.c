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

cy_stc_scb_i2c_master_xfer_config_t gasGaugeWriteCfg =
{
    .slaveAddress = BQ27210_DEVICE_ADDRESS,
    .buffer       = NULL,
    .bufferSize   = 0U,
    .xferPending  = false
};

cy_stc_scb_i2c_master_xfer_config_t gasGaugeReadCfg =
{
    .slaveAddress = BQ27210_DEVICE_ADDRESS,
    .buffer       = NULL,
    .bufferSize   = 0U,
    .xferPending  = false
};

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
	uint8_t numBytes = 1;

    if( ( status = I2C_MasterSendStart(BQ27210_DEVICE_ADDRESS, CY_SCB_I2C_WRITE_XFER , TIMEOUT) ) != CY_SCB_I2C_SUCCESS) {
        printf("Error starting communication: %x\r\n", status);
    }
    
    /* Set to read from buffer at offset */
    gasGaugeWriteCfg.buffer = &offset;
    gasGaugeWriteCfg.bufferSize = numBytes;
    if(I2C_MasterWrite(&gasGaugeWriteCfg) != CY_SCB_I2C_SUCCESS) {
        printf("Error writing to IMU\r\n");   
    }
    
    /* Restart */
    I2C_MasterSendReStart(BQ27210_DEVICE_ADDRESS, CY_SCB_I2C_READ_XFER, TIMEOUT);
    
    /* Read single byte */
    I2C_MasterReadByte(CY_SCB_MASTER_INTR_I2C_NACK, output, TIMEOUT); // Read from register
    
    I2C_MasterSendStop(TIMEOUT); 

    return true;
}

bool readRegisterInt16(int16_t* output, uint8_t offset )
{
    uint8_t localBuffer[2];
    readRegisterRegion(localBuffer, offset, 2);
    *output = (int16_t)localBuffer[0] | (int16_t)(localBuffer[1] << 8);
    
    return true;
}

bool writeRegister(uint8_t offset, uint8_t data)
{
    uint8_t numBytes = 1;

    I2C_MasterSendStart(BQ27210_DEVICE_ADDRESS, CY_SCB_I2C_WRITE_XFER , TIMEOUT);
    
    /* Set to read from buffer at offset */
    gasGaugeWriteCfg.buffer = &offset;
    gasGaugeWriteCfg.bufferSize = numBytes;
    I2C_MasterWrite(&gasGaugeWriteCfg);
    
    /* Set to write data to offset */
    gasGaugeWriteCfg.buffer = &data;
    gasGaugeWriteCfg.bufferSize = 1U;
    I2C_MasterWrite(&gasGaugeWriteCfg);
        
    I2C_MasterSendStop(TIMEOUT);
    
    return true;
}

static bool readRegisterRegion(uint8_t* output, uint8_t offset, uint8_t length)
{    
    I2C_MasterSendStart(BQ27210_DEVICE_ADDRESS, CY_SCB_I2C_WRITE_XFER , TIMEOUT);
    
    /* Set to read from buffer at offset */
    gasGaugeWriteCfg.buffer = &offset;
    gasGaugeWriteCfg.bufferSize = 1U;
    I2C_MasterWrite(&gasGaugeWriteCfg);
    
    /* Restart */
    I2C_MasterSendReStart(BQ27210_DEVICE_ADDRESS, CY_SCB_I2C_READ_XFER, TIMEOUT);
    
    /* Read specified number of bytes */
    gasGaugeReadCfg.buffer = output;
    gasGaugeReadCfg.bufferSize = length;
    I2C_MasterRead(&gasGaugeReadCfg);
    
    I2C_MasterSendStop(TIMEOUT); 

    return true;
}

/* [] END OF FILE */
