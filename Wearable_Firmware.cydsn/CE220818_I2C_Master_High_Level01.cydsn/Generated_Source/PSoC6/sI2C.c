/***************************************************************************//**
* \file sI2C.c
* \version 2.0
*
*  This file provides the source code to the API for the I2C Component.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "sI2C.h"
#include "sysint/cy_sysint.h"
#include "cyfitter_sysint.h"
#include "cyfitter_sysint_cfg.h"


#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*     Global variables
***************************************/

/** sI2C_initVar indicates whether the sI2C
*  component has been initialized. The variable is initialized to 0
*  and set to 1 the first time sI2C_Start() is called.
*  This allows  the component to restart without reinitialization
*  after the first call to the sI2C_Start() routine.
*
*  If re-initialization of the component is required, then the
*  sI2C_Init() function can be called before the
*  sI2C_Start() or sI2C_Enable() function.
*/
uint8_t sI2C_initVar = 0U;

/** The instance-specific configuration structure.
* The pointer to this structure should be passed to Cy_SCB_I2C_Init function
* to initialize component with GUI selected settings.
*/
cy_stc_scb_i2c_config_t const sI2C_config =
{
    .i2cMode    = CY_SCB_I2C_SLAVE,

    .useRxFifo = true,
    .useTxFifo = true,

    .slaveAddress        = 0x24U,
    .slaveAddressMask    = 0xFEU,
    .acceptAddrInFifo    = false,
    .ackGeneralAddr      = false,

    .enableWakeFromSleep = false
};

/** The instance-specific context structure.
* It is used while the driver operation for internal configuration and
* data keeping for the I2C. The user should not modify anything in this
* structure.
*/
cy_stc_scb_i2c_context_t sI2C_context;


/*******************************************************************************
* Function Name: sI2C_Start
****************************************************************************//**
*
* Invokes sI2C_Init() and sI2C_Enable().
* Also configures interrupt and low and high oversampling phases.
* After this function call the component is enabled and ready for operation.
* This is the preferred method to begin component operation.
*
* \globalvars
* \ref sI2C_initVar - used to check initial configuration,
* modified  on first function call.
*
*******************************************************************************/
void sI2C_Start(void)
{
    if (0U == sI2C_initVar)
    {
        /* Configure component */
        (void) Cy_SCB_I2C_Init(sI2C_HW, &sI2C_config, &sI2C_context);

    #if (sI2C_ENABLE_MASTER)
        /* Configure desired data rate */
        (void) Cy_SCB_I2C_SetDataRate(sI2C_HW, sI2C_DATA_RATE_HZ, sI2C_CLK_FREQ_HZ);

        #if (sI2C_MANUAL_SCL_CONTROL)
            Cy_SCB_I2C_MasterSetLowPhaseDutyCycle (sI2C_HW, sI2C_LOW_PHASE_DUTY_CYCLE);
            Cy_SCB_I2C_MasterSetHighPhaseDutyCycle(sI2C_HW, sI2C_HIGH_PHASE_DUTY_CYCLE);
        #endif /* (sI2C_MANUAL_SCL_CONTROL) */
    #endif /* (sI2C_ENABLE_MASTER) */

        /* Hook interrupt service routine */
    #if defined(sI2C_SCB_IRQ__INTC_ASSIGNED)
        (void) Cy_SysInt_Init(&sI2C_SCB_IRQ_cfg, &sI2C_Interrupt);
    #endif /* (sI2C_SCB_IRQ__INTC_ASSIGNED) */

        sI2C_initVar = 1U;
    }

    /* Enable interrupt in NVIC */
#if defined(sI2C_SCB_IRQ__INTC_ASSIGNED)
    NVIC_EnableIRQ((IRQn_Type) sI2C_SCB_IRQ_cfg.intrSrc);
#endif /* (sI2C_SCB_IRQ__INTC_ASSIGNED) */

    Cy_SCB_I2C_Enable(sI2C_HW);
}

#if defined(__cplusplus)
}
#endif


/* [] END OF FILE */
