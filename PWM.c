// Write me!
/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>

/* Project Includes */
#include "PWM.h"

/* Application Defines  */
#define TIMERA0_PERIOD 127


/* Timer_A UpDown Configuration Parameter */
Timer_A_UpDownModeConfig upDownConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,               // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_1,          // SMCLK/1 = 12 MHz
        TIMERA0_PERIOD,                         // 127 tick period
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,    // Disable CCR0 interrupt
        TIMER_A_DO_CLEAR                        // Clear value
};

/* Timer_A Compare Configuration Parameter (PWM3) */
Timer_A_CompareModeConfig compareConfig_PWM3 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_3,          // Use CCR3
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output bit
        TIMERA0_PERIOD                              // Initial 0% Duty Cycle
};

/* Timer_A Compare Configuration Parameter (PWM3) */
Timer_A_CompareModeConfig compareConfig_PWM4 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_4,          // Use CCR4
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output bit
        TIMERA0_PERIOD                              // Initial 0% Duty Cycle
};


/**
 * Initializes PWM output on P2.6 (right motor) using Timer A0 CCR3 interrupt
 * and on P2.7 (left motor) using the Timer A0 CCR4 interrupt
 * Assumes SMCLK has been initialized to 12 MHz
 * @param period the period of the PWM signal in 83.3 us units
 * @param duty3 the desired duty cycle on P2.6 (TA0 CCR3) as a percent (from 0-100)
 * @param duty4 the desired duty cycle on P2.7 (TA0 CCR4) as a percent (from 0-100)
 * @return none
 */
void PWM_Init(uint16_t period, uint16_t duty3, uint16_t duty4){
    /*
    // Reconfigure the port mapping of the CCRs to map to the LEDs
        PMAP_configurePorts((const uint8_t *) port_mapping, PMAP_P2MAP, 1,
                                    PMAP_DISABLE_RECONFIGURATION);
    */

    // do stuff with parameters
    upDownConfig.timerPeriod = period;
    compareConfig_PWM3.compareValue = (((100-duty3)*127)/100); // do i need to convert these duty numbers to CCR numbers ? (((100-duty)*127)/100)
    //compareConfig_PWM3.compareValue = duty3;
    compareConfig_PWM4.compareValue = (((100-duty4)*127)/100);
    //compareConfig_PWM4.compareValue = duty4;


    // Set motors for CCR Output
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2,
                GPIO_PIN6 | GPIO_PIN7 , GPIO_PRIMARY_MODULE_FUNCTION);

    // Configure Timer_A0 for UpDown Mode
    Timer_A_configureUpDownMode(TIMER_A0_BASE, &upDownConfig);

    // Start TimerA0 in UpDown Mode
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UPDOWN_MODE);

    // Initialize compare registers to generate PWM3
    Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM3);

    // Initialize compare registers to generate PWM4
    Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM4);

}

/**
 * Sets the duty cycle of the PWM output on P2.6 (right motor)
 * @param duty3 the desired duty cycle on P2.6 (changes TA0 CCR3)
 * @return none
 */
void PWM_Duty_Right(uint16_t duty1){
    // Convert Duty Cycle into the appropriate CCR Value


    //**************** UNSURE its either 1st or 2nd part

    uint16_t CCR_Value = (((100-duty1)*127)/100);

    // Modify the CCR Value in the configuration
    compareConfig_PWM3.compareValue = CCR_Value;

    // Initialize the timer with the modified configuration
    Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM3);

}

void PWM_Duty_Left(uint16_t duty4){
    // Convert Duty Cycle into the appropriate CCR Value

    uint16_t CCR_Value = (((100-duty4)*127)/100);

    // Modify the CCR Value in the configuration
    compareConfig_PWM4.compareValue = CCR_Value;
    // Initialize the timer with the modified configuration
    Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM4);

}
