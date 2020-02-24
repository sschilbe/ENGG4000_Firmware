/*******************************************************************************
* File Name: RedPWM.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the RedPWM
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(RedPWM_CY_TCPWM_PWM_PDL_H)
#define RedPWM_CY_TCPWM_PWM_PDL_H

#include "cyfitter.h"
#include "tcpwm/cy_tcpwm_pwm.h"

   
/*******************************************************************************
* Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  RedPWM_initVar;
extern cy_stc_tcpwm_pwm_config_t const RedPWM_config;
/** @} group_globals */


/***************************************
*        Function Prototypes
****************************************/
/**
* \addtogroup group_general
* @{
*/
void RedPWM_Start(void);
__STATIC_INLINE cy_en_tcpwm_status_t RedPWM_Init(cy_stc_tcpwm_pwm_config_t const *config);
__STATIC_INLINE void RedPWM_DeInit(void);
__STATIC_INLINE void RedPWM_Enable(void);
__STATIC_INLINE void RedPWM_Disable(void);
__STATIC_INLINE uint32_t RedPWM_GetStatus(void);
__STATIC_INLINE void RedPWM_SetCompare0(uint32_t compare0);
__STATIC_INLINE uint32_t RedPWM_GetCompare0(void);
__STATIC_INLINE void RedPWM_SetCompare1(uint32_t compare1);
__STATIC_INLINE uint32_t RedPWM_GetCompare1(void);
__STATIC_INLINE void RedPWM_EnableCompareSwap(bool enable);
__STATIC_INLINE void RedPWM_SetCounter(uint32_t count);
__STATIC_INLINE uint32_t RedPWM_GetCounter(void);
__STATIC_INLINE void RedPWM_SetPeriod0(uint32_t period0);
__STATIC_INLINE uint32_t RedPWM_GetPeriod0(void);
__STATIC_INLINE void RedPWM_SetPeriod1(uint32_t period1);
__STATIC_INLINE uint32_t RedPWM_GetPeriod1(void);
__STATIC_INLINE void RedPWM_EnablePeriodSwap(bool enable);
__STATIC_INLINE void RedPWM_TriggerStart(void);
__STATIC_INLINE void RedPWM_TriggerReload(void);
__STATIC_INLINE void RedPWM_TriggerKill(void);
__STATIC_INLINE void RedPWM_TriggerSwap(void);
__STATIC_INLINE uint32_t RedPWM_GetInterruptStatus(void);
__STATIC_INLINE void RedPWM_ClearInterrupt(uint32_t source);
__STATIC_INLINE void RedPWM_SetInterrupt(uint32_t source);
__STATIC_INLINE void RedPWM_SetInterruptMask(uint32_t mask);
__STATIC_INLINE uint32_t RedPWM_GetInterruptMask(void);
__STATIC_INLINE uint32_t RedPWM_GetInterruptStatusMasked(void);
/** @} general */


/***************************************
*           API Constants
***************************************/

/**
* \addtogroup group_macros
* @{
*/
/** This is a ptr to the base address of the TCPWM instance */
#define RedPWM_HW                 (RedPWM_TCPWM__HW)

/** This is a ptr to the base address of the TCPWM CNT instance */
#define RedPWM_CNT_HW             (RedPWM_TCPWM__CNT_HW)

/** This is the counter instance number in the selected TCPWM */
#define RedPWM_CNT_NUM            (RedPWM_TCPWM__CNT_IDX)

/** This is the bit field representing the counter instance in the selected TCPWM */
#define RedPWM_CNT_MASK           (1UL << RedPWM_CNT_NUM)
/** @} group_macros */

#define RedPWM_INPUT_MODE_MASK    (0x3U)
#define RedPWM_INPUT_DISABLED     (7U)


/*******************************************************************************
* Function Name: RedPWM_Init
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_tcpwm_status_t RedPWM_Init(cy_stc_tcpwm_pwm_config_t const *config)
{
    return(Cy_TCPWM_PWM_Init(RedPWM_HW, RedPWM_CNT_NUM, config));
}


/*******************************************************************************
* Function Name: RedPWM_DeInit
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_DeInit(void)                   
{
    Cy_TCPWM_PWM_DeInit(RedPWM_HW, RedPWM_CNT_NUM, &RedPWM_config);
}

/*******************************************************************************
* Function Name: RedPWM_Enable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Enable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_Enable(void)                   
{
    Cy_TCPWM_Enable_Multiple(RedPWM_HW, RedPWM_CNT_MASK);
}


/*******************************************************************************
* Function Name: RedPWM_Disable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Disable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_Disable(void)                  
{
    Cy_TCPWM_Disable_Multiple(RedPWM_HW, RedPWM_CNT_MASK);
}


/*******************************************************************************
* Function Name: RedPWM_GetStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t RedPWM_GetStatus(void)                
{
    return(Cy_TCPWM_PWM_GetStatus(RedPWM_HW, RedPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: RedPWM_SetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_SetCompare0(uint32_t compare0)      
{
    Cy_TCPWM_PWM_SetCompare0(RedPWM_HW, RedPWM_CNT_NUM, compare0);
}


/*******************************************************************************
* Function Name: RedPWM_GetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t RedPWM_GetCompare0(void)              
{
    return(Cy_TCPWM_PWM_GetCompare0(RedPWM_HW, RedPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: RedPWM_SetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_SetCompare1(uint32_t compare1)      
{
    Cy_TCPWM_PWM_SetCompare1(RedPWM_HW, RedPWM_CNT_NUM, compare1);
}


/*******************************************************************************
* Function Name: RedPWM_GetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t RedPWM_GetCompare1(void)              
{
    return(Cy_TCPWM_PWM_GetCompare1(RedPWM_HW, RedPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: RedPWM_EnableCompareSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnableCompareSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_EnableCompareSwap(bool enable)  
{
    Cy_TCPWM_PWM_EnableCompareSwap(RedPWM_HW, RedPWM_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: RedPWM_SetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_SetCounter(uint32_t count)          
{
    Cy_TCPWM_PWM_SetCounter(RedPWM_HW, RedPWM_CNT_NUM, count);
}


/*******************************************************************************
* Function Name: RedPWM_GetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t RedPWM_GetCounter(void)               
{
    return(Cy_TCPWM_PWM_GetCounter(RedPWM_HW, RedPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: RedPWM_SetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_SetPeriod0(uint32_t period0)          
{
    Cy_TCPWM_PWM_SetPeriod0(RedPWM_HW, RedPWM_CNT_NUM, period0);
}


/*******************************************************************************
* Function Name: RedPWM_GetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t RedPWM_GetPeriod0(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod0(RedPWM_HW, RedPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: RedPWM_SetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_SetPeriod1(uint32_t period1)
{
    Cy_TCPWM_PWM_SetPeriod1(RedPWM_HW, RedPWM_CNT_NUM, period1);
}


/*******************************************************************************
* Function Name: RedPWM_GetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t RedPWM_GetPeriod1(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod1(RedPWM_HW, RedPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: RedPWM_EnablePeriodSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnablePeriodSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_EnablePeriodSwap(bool enable)
{
    Cy_TCPWM_PWM_EnablePeriodSwap(RedPWM_HW, RedPWM_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: RedPWM_TriggerStart
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_TriggerStart(void)             
{
    Cy_TCPWM_TriggerStart(RedPWM_HW, RedPWM_CNT_MASK);
}


/*******************************************************************************
* Function Name: RedPWM_TriggerReload
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerReloadOrIndex() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_TriggerReload(void)     
{
    Cy_TCPWM_TriggerReloadOrIndex(RedPWM_HW, RedPWM_CNT_MASK);
}


/*******************************************************************************
* Function Name: RedPWM_TriggerKill
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStopOrKill() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_TriggerKill(void)
{
    Cy_TCPWM_TriggerStopOrKill(RedPWM_HW, RedPWM_CNT_MASK);
}


/*******************************************************************************
* Function Name: RedPWM_TriggerSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerCaptureOrSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_TriggerSwap(void)     
{
    Cy_TCPWM_TriggerCaptureOrSwap(RedPWM_HW, RedPWM_CNT_MASK);
}


/*******************************************************************************
* Function Name: RedPWM_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t RedPWM_GetInterruptStatus(void)       
{
    return(Cy_TCPWM_GetInterruptStatus(RedPWM_HW, RedPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: RedPWM_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_ClearInterrupt(uint32_t source)     
{
    Cy_TCPWM_ClearInterrupt(RedPWM_HW, RedPWM_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: RedPWM_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_SetInterrupt(uint32_t source)
{
    Cy_TCPWM_SetInterrupt(RedPWM_HW, RedPWM_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: RedPWM_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void RedPWM_SetInterruptMask(uint32_t mask)     
{
    Cy_TCPWM_SetInterruptMask(RedPWM_HW, RedPWM_CNT_NUM, mask);
}


/*******************************************************************************
* Function Name: RedPWM_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t RedPWM_GetInterruptMask(void)         
{
    return(Cy_TCPWM_GetInterruptMask(RedPWM_HW, RedPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: RedPWM_GetInterruptStatusMasked
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t RedPWM_GetInterruptStatusMasked(void)
{
    return(Cy_TCPWM_GetInterruptStatusMasked(RedPWM_HW, RedPWM_CNT_NUM));
}

#endif /* RedPWM_CY_TCPWM_PWM_PDL_H */


/* [] END OF FILE */
