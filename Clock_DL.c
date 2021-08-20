/*
 * Clock_DL.c
 *
 */


/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
/* Project Includes */
#include "Clock.h"
#include "msp.h"
#include "GPIO.h"
#include "PCM.h"
#include "FLASH.h"
#include "CS.h"

/*
 * HFXT_Init TODO:
 * Initialize HFXT oscillator in the power state allowing for maximum operating frequency of 48 MHz
 * 1. Set appropriate PJ pins to HFXT in/out mode
 * 2. Enable higher power state to allow 48 MHZ operation
 * 3. Set wait state for flash controllers (must be called when changing clock frequency ranges)
 * 4. Set start HFXT
 */
void HFXT_Init(void){
    //1
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN3 | GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
        GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
        //2
        PCM_setCoreVoltageLevel(PCM_VCORE1);
        //3
        FlashCtl_setWaitState(FLASH_BANK0, 2);
        FlashCtl_setWaitState(FLASH_BANK1, 2);
        //4 (change?)
        CS_startHFXT(false);

}

/*
 * Clock_Init TODO:
 * 1. Set frequency for HFXT crystal to 48MHz
 * 2. Call HFXT_Init
 * 3. Init MCLK to 48MHz
 * 4. Init SMCLK to 12MHz (1/4 of MCLK)
 */
void Clock_Init(){
    CS_setExternalClockSourceFrequency(32000, 48000000);
    HFXT_Init();
    CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_4); //divider 4 bc we dont need to divide anything
}

// ------------Clock_Delay1us------------
// Simple delay function which delays about n microseconds.
// Inputs: n, number of us to wait
// Outputs: none
void Clock_Delay1us(uint32_t n){
  n = (382*n)/100;; // 1 us, tuned at 48 MHz
  while(n){
    n--;
  }
}

// delay function
// which delays about 6*ulCount cycles
// ulCount=8000 => 1ms = (8000 loops)*(6 cycles/loop)*(20.83 ns/cycle)
  //Code Composer Studio Code
void delay(unsigned long ulCount){
  __asm (  "pdloop:  subs    r0, #1\n"
      "    bne    pdloop\n");
}

// ------------Clock_Delay1ms------------
// Simple delay function which delays about n milliseconds.
// Inputs: n, number of msec to wait
// Outputs: none
void Clock_Delay1ms(uint32_t n){
  while(n){
    delay(48000000/9162);   // 1 msec, tuned at 48 MHz
    n--;
  }
}




