/* DriverLib Includes */
#include "driverlib.h"
#include <stdio.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

/* Project Includes */
#include "TimerA1.h"
#include "msp.h"
#include "Reflectance.h"
#include "Bump.h"

//counter for when interrupts should be handled
int counter = 1;

//configuration for the UP mode for Timer A
Timer_A_UpModeConfig Config =
    {
     TIMER_A_CLOCKSOURCE_SMCLK, // use SMCLK as timer source
     TIMER_A_CLOCKSOURCE_DIVIDER_12, // 12Mhz / 12 = 1Mhz
     1, // 1 as default, this is changed in INIT
     TIMER_A_TAIE_INTERRUPT_DISABLE,
     TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE, // enable wanted interrupt
     TIMER_A_DO_CLEAR // clear timer
    };

// Initializes Timer A1 in up mode and triggers a periodic interrupt at a desired frequency
void TimerA1_Init(uint16_t period){
    //config period is set
    Config.timerPeriod = period;
    //configure up mode
    Timer_A_configureUpMode(TIMER_A1_BASE, &Config );
    //enable interrupt
    Interrupt_enableInterrupt(INT_TA1_0);
    //start timer
    Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_UP_MODE);

}

// stops Timer A1
void TimerA1_Stop(void){
    Timer_A_stopTimer(TIMER_A1_BASE);

    //the control register of A1 (CTL) is masked with 0xCF, so bit 4 and 5 are set to 0 (STOP mode) and the rest are kept the same.
    //TIMER_A1->CTL &=0xCF;
    
}

// start Timer A1
void TimerA1_Start(void){
    //start timer
    Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_UP_MODE);

}

// ISR function for Timer A1 periodic interrupt
void TA1_0_IRQHandler(void){
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
    //call reflectance start every 10th interrupt starting with the first one
    if (counter % 10 == 0 || counter == 1){
        Reflectance_Start();
    }
    //call reflectance end every 10th interrupt starting with the 2nd
    else if ((counter-1) % 10 == 0 || counter == 2){
        Reflectance_End();
    }
    //call bump read every 3rd interrupt starting with the 3rd
    else if ((counter-2)% 10 == 0 || counter == 3){
        Bump_Read();
    }
    else{
    }
    //increment counter
    counter ++;


}
