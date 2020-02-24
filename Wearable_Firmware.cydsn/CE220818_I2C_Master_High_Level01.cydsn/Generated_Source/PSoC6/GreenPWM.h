/*******************************************************************************
* File Name: GreenPWM.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the GreenPWM
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(GreenPWM_CY_TCPWM_PWM_PDL_H)
#define GreenPWM_CY_TCPWM_PWM_PDL_H

#include "cyfitter.h"
#include "tcpwm/cy_tcpwm_pwm.h"

   
/*******************************************************************************
* Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  GreenPWM_initVar;
extern cy_stc_tcpwm_pwm_config_t const GreenPWM_config;
/** @} group_globals */


/***************************************
*        Function Prototypes
****************************************/
/**
* \addtogroup group_general
* @{
*/
void GreenPWM_Start(void);
__STATIC_INLINE cy_en_tcpwm_status_t GreenPWM_Init(cy_stc_tcpwm_pwm_config_t const *config);
__STATIC_INLINE void GreenPWM_DeInit(void);
__STATIC_INLINE void GreenPWM_Enable(void);
__STATIC_INLINE void GreenPWM_Disable(void);
__STATIC_INLINE uint32_t GreenPWM_GetStatus(void);
__STATIC_INLINE void GreenPWM_SetCompare0(uint32_t compare0);
__STATIC_INLINE uint32_t GreenPWM_GetCompare0(void);
__STATIC_INLINE void GreenPWM_SetCompare1(uint32_t compare1);
__STATIC_INLINE uint32_t GreenPWM_GetCompare1(void);
__STATIC_INLINE void GreenPWM_EnableCompareSwap(bool enable);
__STATIC_INLINE void GreenPWM_SetCounter(uint32_t count);
__STATIC_INLINE uint32_t GreenPWM_GetCounter(void);
__STATIC_INLINE void GreenPWM_SetPeriod0(uint32_t period0);
__STATIC_INLINE uint32_t GreenPWM_GetPeriod0(void);
__STATIC_INLINE void GreenPWM_SetPeriod1(uint32_t period1);
__STATIC_INLINE uint32_t GreenPWM_GetPeriod1(void);
__STATIC_INLINE void GreenPWM_EnablePeriodSwap(bool enable);
__STATIC_INLINE void GreenPWM_TriggerStart(void);
__STATIC_INLINE void GreenPWM_TriggerReload(void);
__STATIC_INLINE void GreenPWM_TriggerKill(void);
__STATIC_INLINE void GreenPWM_TriggerSwap(void);
__STATIC_INLINE uint32_t GreenPWM_GetInterruptStatus(void);
__STATIC_INLINE void GreenPWM_ClearInterrupt(uint32_t source);
__STATIC_INLINE void GreenPWM_SetInterrupt(uint32_t source);
__STATIC_INLINE void GreenPWM_SetInterruptMask(uint32_t mask);
__STATIC_INLINE uint32_t GreenPWM_GetInterruptMask(void);
__STATIC_INLINE uint32_t GreenPWM_GetInterruptStatusMasked(void);
/** @} general */


/***************************************
*           API Constants
***************************************/

/**
* \addtogroup group_macros
* @{
*/
/** This is a ptr to the base address of the TCPWM instance */
#define GreenPWM_HW                 (GreenPWM_TCPWM__HW)

/** This is a ptr to the base address of the TCPWM CNT instance */
#define GreenPWM_CNT_HW             (GreenPWM_TCPWM__CNT_HW)

/** This is the counter instance number in the selected TCPWM */
#define GreenPWM_CNT_NUM            (GreenPWM_TCPWM__CNT_IDX)

/** This is the bit field representing the counter instance in the selected TCPWM */
#define GreenPWM_CNT_MASK           (1UL << GreenPWM_CNT_NUM)
/** @} group_macros */

#define GreenPWM_INPUT_MODE_MASK    (0x3U)
#define GreenPWM_INPUT_DISABLED     (7U)


/*******************************************************************************
* Function Name: GreenPWM_Init
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_tcpwm_status_t GreenPWM_Init(cy_stc_tcpwm_pwm_config_t const *config)
{
    return(Cy_TCPWM_PWM_Init(GreenPWM_HW, GreenPWM_CNT_NUM, config));
}


/*******************************************************************************
* Function Name: GreenPWM_DeInit
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_DeInit(void)                   
{
    Cy_TCPWM_PWM_DeInit(GreenPWM_HW, GreenPWM_CNT_NUM, &GreenPWM_config);
}

/*******************************************************************************
* Function Name: GreenPWM_Enable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Enable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_Enable(void)                   
{
    Cy_TCPWM_Enable_Multiple(GreenPWM_HW, GreenPWM_CNT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_Disable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Disable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_Disable(void)                  
{
    Cy_TCPWM_Disable_Multiple(GreenPWM_HW, GreenPWM_CNT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_GetStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t GreenPWM_GetStatus(void)                
{
    return(Cy_TCPWM_PWM_GetStatus(GreenPWM_HW, GreenPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: GreenPWM_SetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_SetCompare0(uint32_t compare0)      
{
    Cy_TCPWM_PWM_SetCompare0(GreenPWM_HW, GreenPWM_CNT_NUM, compare0);
}


/*******************************************************************************
* Function Name: GreenPWM_GetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t GreenPWM_GetCompare0(void)              
{
    return(Cy_TCPWM_PWM_GetCompare0(GreenPWM_HW, GreenPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: GreenPWM_SetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_SetCompare1(uint32_t compare1)      
{
    Cy_TCPWM_PWM_SetCompare1(GreenPWM_HW, GreenPWM_CNT_NUM, compare1);
}


/*******************************************************************************
* Function Name: GreenPWM_GetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t GreenPWM_GetCompare1(void)              
{
    return(Cy_TCPWM_PWM_GetCompare1(GreenPWM_HW, GreenPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: GreenPWM_EnableCompareSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnableCompareSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_EnableCompareSwap(bool enable)  
{
    Cy_TCPWM_PWM_EnableCompareSwap(GreenPWM_HW, GreenPWM_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: GreenPWM_SetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_SetCounter(uint32_t count)          
{
    Cy_TCPWM_PWM_SetCounter(GreenPWM_HW, GreenPWM_CNT_NUM, count);
}


/*******************************************************************************
* Function Name: GreenPWM_GetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t GreenPWM_GetCounter(void)               
{
    return(Cy_TCPWM_PWM_GetCounter(GreenPWM_HW, GreenPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: GreenPWM_SetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_SetPeriod0(uint32_t period0)          
{
    Cy_TCPWM_PWM_SetPeriod0(GreenPWM_HW, GreenPWM_CNT_NUM, period0);
}


/*******************************************************************************
* Function Name: GreenPWM_GetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t GreenPWM_GetPeriod0(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod0(GreenPWM_HW, GreenPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: GreenPWM_SetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_SetPeriod1(uint32_t period1)
{
    Cy_TCPWM_PWM_SetPeriod1(GreenPWM_HW, GreenPWM_CNT_NUM, period1);
}


/*******************************************************************************
* Function Name: GreenPWM_GetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t GreenPWM_GetPeriod1(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod1(GreenPWM_HW, GreenPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: GreenPWM_EnablePeriodSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnablePeriodSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_EnablePeriodSwap(bool enable)
{
    Cy_TCPWM_PWM_EnablePeriodSwap(GreenPWM_HW, GreenPWM_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: GreenPWM_TriggerStart
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_TriggerStart(void)             
{
    Cy_TCPWM_TriggerStart(GreenPWM_HW, GreenPWM_CNT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_TriggerReload
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerReloadOrIndex() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_TriggerReload(void)     
{
    Cy_TCPWM_TriggerReloadOrIndex(GreenPWM_HW, GreenPWM_CNT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_TriggerKill
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStopOrKill() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_TriggerKill(void)
{
    Cy_TCPWM_TriggerStopOrKill(GreenPWM_HW, GreenPWM_CNT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_TriggerSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerCaptureOrSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_TriggerSwap(void)     
{
    Cy_TCPWM_TriggerCaptureOrSwap(GreenPWM_HW, GreenPWM_CNT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t GreenPWM_GetInterruptStatus(void)       
{
    return(Cy_TCPWM_GetInterruptStatus(GreenPWM_HW, GreenPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: GreenPWM_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_ClearInterrupt(uint32_t source)     
{
    Cy_TCPWM_ClearInterrupt(GreenPWM_HW, GreenPWM_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: GreenPWM_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_SetInterrupt(uint32_t source)
{
    Cy_TCPWM_SetInterrupt(GreenPWM_HW, GreenPWM_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: GreenPWM_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void GreenPWM_SetInterruptMask(uint32_t mask)     
{
    Cy_TCPWM_SetInterruptMask(GreenPWM_HW, GreenPWM_CNT_NUM, mask);
}


/*******************************************************************************
* Function Name: GreenPWM_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t GreenPWM_GetInterruptMask(void)         
{
    return(Cy_TCPWM_GetInterruptMask(GreenPWM_HW, GreenPWM_CNT_NUM));
}


/*******************************************************************************
* Function Name: GreenPWM_GetInterruptStatusMasked
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t GreenPWM_GetInterruptStatusMasked(void)
{
    return(Cy_TCPWM_GetInterruptStatusMasked(GreenPWM_HW, GreenPWM_CNT_NUM));
}

#endif /* GreenPWM_CY_TCPWM_PWM_PDL_H */


/* [] END OF FILE */
