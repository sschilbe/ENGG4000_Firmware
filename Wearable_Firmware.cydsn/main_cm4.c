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

/* I2C interface */
#include "common_i2c.h"

/* IMU Control */
#include "imu_LSM6DS3.h"

/* Gas Gauge Control */
#include "gas_gauge_BQ27210.h"

void TimerInterruptHandler(void)
{
    int16_t x_value = 0;
    
    /* Clear the interrupt flag */
    Cy_TCPWM_ClearInterrupt(Timer_HW, Timer_CNT_NUM, CY_TCPWM_INT_ON_TC);
    sendNotifications();
    
    x_value = readRawAccelX();
    printf("X value is: %d\r\n", x_value);
}

// Starts the system
int main(void)
{
    /* Initialize the interrupt vector table with the timer interrupt handler
     * address and assign priority.
     */
    Cy_SCB_I2C_Init(I2C_HW, &I2C_config, &I2C_context);
    Cy_SCB_I2C_SetDataRate(I2C_HW, I2C_DATA_RATE_HZ, I2C_CLK_FREQ_HZ);
    Cy_SysInt_Init(&I2C_SCB_IRQ_cfg, &I2C_Interrupt);
    
    Cy_SysInt_Init(&isrTimer_cfg, TimerInterruptHandler);
    
    /* Enable interrupt in NVIC. */
    NVIC_EnableIRQ((IRQn_Type) I2C_SCB_IRQ_cfg.intrSrc);
    
    /* Enable I2C master hardware. */
    Cy_SCB_I2C_Enable(I2C_HW);
    
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

    if( !imuInit() )
    {
        printf("Error validating the identity of the IMU");    
    }
    
    gasGaugeInit();
    
    imuConfigure();
    gasGaugeConfigure();
    
    BleInit();
    
    for(;;)
    {
        Cy_BLE_ProcessEvents();
        
        /* Entering into the Deep Sleep */
        //Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
}

/* [] END OF FILE */
