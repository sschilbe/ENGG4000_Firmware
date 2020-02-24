/**
*
* @file
* imu_LSM6DS3.c
*
* @brief
* Implementation for controlling the IMU over I2C
*
* Note: This implementation is heavily influenced by the Arduino library
* available for this component, supplied by Sparkfun
*
* Author: Schilbe, Seth
*Date: 2019 - 02 - 19 */

/*------------------------------------------------------------
INCLUDES
------------------------------------------------------------*/
#include "common_i2c.h"
#include "imu_LSM6DS3.h"

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
//This struct holds the settings the driver uses to do calculations
typedef struct imu_settings_s {
	//Gyro settings
	bool                            gyroEnabled;
	LSM6DS3_ACC_GYRO_FS_G_t         gyroRange;
	LSM6DS3_ACC_GYRO_ODR_G_t        gyroSampleRate;
	LSM6DS3_ACC_GYRO_BW_XL_t        gyroBandWidth;

	bool                            gyroFifoEnabled;
	LSM6DS3_ACC_GYRO_DEC_FIFO_XL_t  gyroFifoDecimation;

	//Accelerometer settings
	bool                            accelEnabled;
	bool                            accelODROff;
	LSM6DS3_ACC_GYRO_FS_XL_t        accelRange;
	LSM6DS3_ACC_GYRO_ODR_G_t        accelSampleRate;
	LSM6DS3_ACC_GYRO_BW_XL_t        accelBandWidth;
	
	bool                            accelFifoEnabled;
	LSM6DS3_ACC_GYRO_DEC_FIFO_XL_t  accelFifoDecimation;
	
	//Temperature settings
	bool                            tempEnabled;

	//FIFO control data
	uint16_t fifoThreshold;         // Can be 0 to 4096
	LSM6DS3_ACC_GYRO_ODR_FIFO_t     fifoSampleRate;
	LSM6DS3_ACC_GYRO_FIFO_MODE_t    fifoModeWord;	
} imu_settings_t;

/*------------------------------------------------------------
MEMORY CONSTANTS
------------------------------------------------------------*/

/*------------------------------------------------------------
VARIABLES
------------------------------------------------------------*/
imu_settings_t imu_configuration =
{
    //Construct with these default settings
    
    .gyroEnabled = true,                            //Can be 0 or 1
    .gyroRange = LSM6DS3_ACC_GYRO_FS_G_2000dps,     //Max deg/s.  Can be: 125, 245, 500, 1000, 2000
    .gyroSampleRate = LSM6DS3_ACC_GYRO_ODR_G_833Hz, //Hz.  Can be: 13, 26, 52, 104, 208, 416, 833,
    .gyroBandWidth = LSM6DS3_ACC_GYRO_BW_XL_400Hz,  //Hz.  Can be: 50, 100, 200, 400;
    .gyroFifoEnabled = true,                        //Set to include gyro in FIFO
    .gyroFifoDecimation = LSM6DS3_ACC_GYRO_DEC_FIFO_XL_NO_DECIMATION,   //set 1 for on /1
    
    .accelEnabled = true,       //Can be 0 or 1
    .accelODROff = true,
    .accelRange = LSM6DS3_ACC_GYRO_FS_XL_16g,           //Max G force readable.  Can be: 2, 4, 8, 16
    .accelSampleRate = LSM6DS3_ACC_GYRO_ODR_G_416Hz,    //Hz.  Can be: 13, 26, 52, 104, 208, 416, 833,
    .accelBandWidth = LSM6DS3_ACC_GYRO_BW_XL_400Hz,     //Hz.  Can be: 50, 100, 200, 400;
    .accelFifoEnabled = true,                           //Set to include accelerometer in the FIFO
    .accelFifoDecimation = LSM6DS3_ACC_GYRO_DEC_FIFO_XL_NO_DECIMATION,  //set 1 for on /1
    
    .tempEnabled = false,   //Can be 0 or 1
    
    //FIFO control data
    .fifoThreshold = 3000,                              //Can be 0 to 4096 (16 b
    .fifoSampleRate = LSM6DS3_ACC_GYRO_ODR_FIFO_10Hz,   //default 10Hz
    .fifoModeWord = LSM6DS3_ACC_GYRO_FIFO_MODE_BYPASS   //Default off
};

cy_stc_scb_i2c_master_xfer_config_t imuWriteCfg =
{
    .slaveAddress = LSM6DS3_DEVICE_ADDRESS,
    .buffer       = NULL,
    .bufferSize   = 0U,
    .xferPending  = false
};

cy_stc_scb_i2c_master_xfer_config_t imuReadCfg =
{
    .slaveAddress = LSM6DS3_DEVICE_ADDRESS,
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
bool readRegisterInt16(int16_t* output, uint8_t offset);

bool imuInit()
{
    //Check the ID register to determine if the operation was a success.
    uint8_t readCheck;
    readRegister(&readCheck, LSM6DS3_ACC_GYRO_WHO_AM_I_REG);
    if( readCheck != LSM6DS3_DEVICE_ADDRESS )
    {
        return false;
    }
    
    return true;
}

void imuConfigure()
{
    uint8_t data_to_write = 0; // Start fresh
    
    /*---------------------------------------
     *   ACCELEROMETER CONFIG
     *--------------------------------------*/
    if( imu_configuration.accelEnabled )
    {
        data_to_write |= imu_configuration.accelBandWidth;
        data_to_write |= imu_configuration.accelRange;
        data_to_write |= imu_configuration.accelSampleRate;
    }
    
	//Now, write the patched together data
	writeRegister(LSM6DS3_ACC_GYRO_CTRL1_XL, data_to_write);

	//Set the ODR bit
	readRegister(&data_to_write, LSM6DS3_ACC_GYRO_CTRL4_C);
	data_to_write &= ~((uint8_t)LSM6DS3_ACC_GYRO_BW_SCAL_ODR_ENABLED);
	if ( imu_configuration.accelODROff ) {
		data_to_write |= LSM6DS3_ACC_GYRO_BW_SCAL_ODR_ENABLED;
	}
    
	writeRegister(LSM6DS3_ACC_GYRO_CTRL4_C, data_to_write);

    /*---------------------------------------
     *   GYROSCOPE CONFIG
     *--------------------------------------*/
    data_to_write = 0; //Start Fresh!
    if( imu_configuration.gyroEnabled )
    {
        data_to_write |= imu_configuration.gyroRange;
        data_to_write |= imu_configuration.gyroSampleRate;
    }
    
    //Write the byte
	writeRegister(LSM6DS3_ACC_GYRO_CTRL2_G, data_to_write);

    // Hope it all worked
}

bool readRegister(uint8_t* output, uint8_t offset)
{
    cy_en_scb_i2c_status_t status;
	uint8_t numBytes = 1;

    if( ( status = I2C_MasterSendStart(LSM6DS3_DEVICE_ADDRESS, CY_SCB_I2C_WRITE_XFER , TIMEOUT) ) != CY_SCB_I2C_SUCCESS) {
        printf("Error starting communication: %x\r\n", status);
    }
    
    /* Set to read from buffer at offset */
    imuWriteCfg.buffer = &offset;
    imuWriteCfg.bufferSize = numBytes;
    if(I2C_MasterWrite(&imuWriteCfg) != CY_SCB_I2C_SUCCESS) {
        printf("Error writing to IMU\r\n");   
    }
    
    /* Restart */
    I2C_MasterSendReStart(LSM6DS3_DEVICE_ADDRESS, CY_SCB_I2C_READ_XFER, TIMEOUT);
    
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

    I2C_MasterSendStart(LSM6DS3_DEVICE_ADDRESS, CY_SCB_I2C_WRITE_XFER , TIMEOUT);
    
    /* Set to read from buffer at offset */
    imuWriteCfg.buffer = &offset;
    imuWriteCfg.bufferSize = numBytes;
    I2C_MasterWrite(&imuWriteCfg);
    
    /* Set to write data to offset */
    imuWriteCfg.buffer = &data;
    imuWriteCfg.bufferSize = 1U;
    I2C_MasterWrite(&imuWriteCfg);
        
    I2C_MasterSendStop(TIMEOUT);
    
    return true;
}

static bool readRegisterRegion(uint8_t* output, uint8_t offset, uint8_t length)
{    
    I2C_MasterSendStart(LSM6DS3_DEVICE_ADDRESS, CY_SCB_I2C_WRITE_XFER , TIMEOUT);
    
    /* Set to read from buffer at offset */
    imuWriteCfg.buffer = &offset;
    imuWriteCfg.bufferSize = 1U;
    I2C_MasterWrite(&imuWriteCfg);
    
    /* Restart */
    I2C_MasterSendReStart(LSM6DS3_DEVICE_ADDRESS, CY_SCB_I2C_READ_XFER, TIMEOUT);
    
    /* Read specified number of bytes */
    imuReadCfg.buffer = output;
    imuReadCfg.bufferSize = length;
    I2C_MasterRead(&imuReadCfg);
    
    I2C_MasterSendStop(TIMEOUT); 

    return true;
}

static int16_t readRaw( uint8_t offset )
{
    int16_t output;
	readRegisterInt16( &output, offset );
    
    return output;
}

int16_t readRawAccelX( void )
{
    return readRaw( LSM6DS3_ACC_GYRO_OUTX_L_XL );
}

int16_t readRawAccelY( void )
{
    return readRaw( LSM6DS3_ACC_GYRO_OUTY_L_XL );
}

int16_t readRawAccelZ( void )
{
    return readRaw( LSM6DS3_ACC_GYRO_OUTZ_L_XL );
}

int16_t readRawGyroX( void )
{
    return readRaw( LSM6DS3_ACC_GYRO_OUTX_L_G );
}

int16_t readRawGyroY( void )
{
    return readRaw( LSM6DS3_ACC_GYRO_OUTY_L_G );
}

int16_t readRawGyroZ( void )
{
    return readRaw( LSM6DS3_ACC_GYRO_OUTZ_L_G );
}

/* [] END OF FILE */
