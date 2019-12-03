/*******************************************************************************
* File Name: PWM_GREEN_BLINK.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the PWM_GREEN_BLINK
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_GREEN_BLINK.h"

/** Indicates whether or not the PWM_GREEN_BLINK has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  PWM_GREEN_BLINK_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the PWM_GREEN_BLINK_Start() routine.
*/
uint8_t PWM_GREEN_BLINK_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated PWM_GREEN_BLINK_Init() function.
*/ 
cy_stc_tcpwm_pwm_config_t const PWM_GREEN_BLINK_config =
{
    .pwmMode = 4UL,
    .clockPrescaler = 0UL,
    .pwmAlignment = 0UL,
    .deadTimeClocks = 0UL,
    .runMode = 0UL,
    .period0 = 5000UL,
    .period1 = 32768UL,
    .enablePeriodSwap = false,
    .compare0 = 100UL,
    .compare1 = 16384UL,
    .enableCompareSwap = false,
    .interruptSources = 0UL,
    .invertPWMOut = 1UL,
    .invertPWMOutN = 0UL,
    .killMode = 2UL,
    .swapInputMode = 3UL,
    .swapInput = CY_TCPWM_INPUT_CREATOR,
    .reloadInputMode = 3UL,
    .reloadInput = CY_TCPWM_INPUT_CREATOR,
    .startInputMode = 3UL,
    .startInput = CY_TCPWM_INPUT_CREATOR,
    .killInputMode = 3UL,
    .killInput = CY_TCPWM_INPUT_CREATOR,
    .countInputMode = 3UL,
    .countInput = CY_TCPWM_INPUT_CREATOR,
};


/*******************************************************************************
* Function Name: PWM_GREEN_BLINK_Start
****************************************************************************//**
*
*  Calls the PWM_GREEN_BLINK_Init() when called the first time and enables 
*  the PWM_GREEN_BLINK. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref PWM_GREEN_BLINK_initVar
*
*******************************************************************************/
void PWM_GREEN_BLINK_Start(void)
{
    if (0U == PWM_GREEN_BLINK_initVar)
    {
        (void) Cy_TCPWM_PWM_Init(PWM_GREEN_BLINK_HW, PWM_GREEN_BLINK_CNT_NUM, &PWM_GREEN_BLINK_config);

        PWM_GREEN_BLINK_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(PWM_GREEN_BLINK_HW, PWM_GREEN_BLINK_CNT_MASK);
    
    #if (PWM_GREEN_BLINK_INPUT_DISABLED == 7UL)
        Cy_TCPWM_TriggerStart(PWM_GREEN_BLINK_HW, PWM_GREEN_BLINK_CNT_MASK);
    #endif /* (PWM_GREEN_BLINK_INPUT_DISABLED == 7UL) */    
}


/* [] END OF FILE */
