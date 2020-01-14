/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <stdio.h>

/* BLE interface */
#include "common_ble.h"

/* ADC interface */
#include "force_adc.h"

/* IMU interface */
#include "imu_i2c.h"

// Starts the system
int main(void)
{
    /* Initialize the interrupt vector table with the timer interrupt handler
     * address and assign priority.
     */
    Cy_SysInt_Init(&isrTimer_cfg, TimerInterruptHandler);
    NVIC_EnableIRQ(isrTimer_cfg.intrSrc); /* Enable the core interrupt */
    __enable_irq(); /* Enable global interrupts. */
    
    /* Start the TCPWM component in timer/counter mode. The return value of the
     * function indicates whether the arguments are valid or not. It is not used
     * here for simplicity. 
     */
    (void)Cy_TCPWM_Counter_Init(Timer_HW, Timer_CNT_NUM, &Timer_config); 
    Cy_TCPWM_Enable_Multiple(Timer_HW, Timer_CNT_MASK); /* Enable the counter instance */

    UART_1_Start();
    setvbuf( stdin, NULL, _IONBF, 0 ); 
    setvbuf( stdout, NULL, _IONBF, 0 ); 
    printf("System Started\r\n");

    /* Trigger a software start on the counter instance. This is required when 
     * no other hardware input signal is connected to the component to act as
     * a trigger source. 
     */
    Cy_TCPWM_TriggerStart(Timer_HW, Timer_CNT_MASK); 

    adcInit();
    i2cInit();
    BleInit();
    
    for(;;)
    {
        Cy_BLE_ProcessEvents();
        
        /* Entering into the Deep Sleep */
        //Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
}

/* [] END OF FILE */
