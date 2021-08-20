/* DriverLib Includes */
//#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "GPIO.h"
#include "interrupt.h"
//#include <ti/devices/msp432p4xx/inc/msp.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

/* Project Includes */
#include "Bump.h"

// Define statements for bump switch pins
#define BUMP_PORT   GPIO_PORT_P4
#define BUMP0       GPIO_PIN0   // P4.0
#define BUMP1       GPIO_PIN2   // P4.2
#define BUMP2       GPIO_PIN3   // P4.3
#define BUMP3       GPIO_PIN5   // P4.5
#define BUMP4       GPIO_PIN6   // P4.6
#define BUMP5       GPIO_PIN7   // P4.7
#define BUMP_PINS   (BUMP0 | BUMP1 | BUMP2| BUMP3| BUMP4 | BUMP5)


uint8_t bumpResult;

// Initialize the bump switch pins as GPIO inputs with pull up resistors
// Switches are active low
void Bump_Init(void){
    //Write this for Interrupt Module warm-up
    GPIO_setAsInputPinWithPullUpResistor(BUMP_PORT, BUMP_PINS);
}

// reads values of bump switches
//gives result with positive logic
uint8_t Bump_Read(void){
    //write this for Interrupt Module warm-up
    // Here we get each pin value and assign it to a variable for ease of use later
        uint8_t b0 = GPIO_getInputPinValue(BUMP_PORT, BUMP0);
        uint8_t b1 = GPIO_getInputPinValue(BUMP_PORT, BUMP1);
        uint8_t b2 = GPIO_getInputPinValue(BUMP_PORT, BUMP2);
        uint8_t b3 = GPIO_getInputPinValue(BUMP_PORT, BUMP3);
        uint8_t b4 = GPIO_getInputPinValue(BUMP_PORT, BUMP4);
        uint8_t b5 = GPIO_getInputPinValue(BUMP_PORT, BUMP5);

        //uint8_t bumpResult;
        //One by one the "result" which is our 8 bit value is built. This is done by bit shifting each value in place.
        bumpResult = 0 << 7;
        bumpResult |= 0 << 6;
        bumpResult |= !b5 << 5;
        bumpResult |= !b4 << 4;
        bumpResult |= !b3 << 3;
        bumpResult |= !b2 << 2;
        bumpResult |= !b1 << 1;
        bumpResult |= !b0;

        //printf("%d\n",bumpResult);

        return bumpResult;
}


#define BUMP_INTERRUPT_PRIORITY 0
void (*BumpTask)(uint8_t bumpData); // function pointer for user task when bump interrupt is detected

// Initializes the bump switch pins and enables Port 4 GPIO interrupts
void Bump_Interrupt_Init(void(*task)(uint8_t)){
    //Write this for Interrupt Module Race-Day
    // set BumpTask to be then user function to be called in ISR,
    BumpTask = task;

    // initialize bump pins as GPIO inputs with pull up resistors
    Bump_Init();

    // configure falling edge interrupts on bump pins
    GPIO_interruptEdgeSelect(BUMP_PORT, BUMP_PINS, GPIO_HIGH_TO_LOW_TRANSITION);

    // clear interrupt flags on bump pins
    GPIO_clearInterruptFlag(BUMP_PORT, BUMP_PINS);

    // enable interrupts with GPIO on the bump pins
    GPIO_enableInterrupt(BUMP_PORT, BUMP_PINS);

    // enable the P4 interrupts in the NVIC
    //so basically set ISER1 to 1
    //PORT4_IRQHandler = 1;
    Interrupt_enableInterrupt(INT_PORT4);


    // set the bump interrupts to the desired priority (remember to shift it to the corect location)
    // (somePriority << 5) where somePriority is 0to7
    Interrupt_setPriority(INT_PORT4, 0 << 5);

}


// ISR for bump interrupts
// clear interrupt flag, read bump switches, and call user function for handling a collision
// there is only one line of code for you to add to this function, that is the call to the DL function 
// that clears the interrupt flag.
void PORT4_IRQHandler(void){
    uint8_t bumpData;
    //write this for Interrupt Module Race-Day
    // read bump switch data to be passed to the bump task
    bumpData = Bump_Read();

    // Call the bump task with the bumpData
    BumpTask(bumpData);


    // clear interrupt flags
    GPIO_clearInterruptFlag(BUMP_PORT, BUMP_PINS);
}


/*
 *
 * Below is switch bounce experiment code
 *


void PORT4_IRQHandler(void){
    uint8_t bumpData;
    //write this for Interrupt Module Race-Day
    // read bump switch data to be passed to the bump task
    bumpData = Bump_Read();


    // clear interrupt flags
    GPIO_clearInterruptFlag(BUMP_PORT, BUMP_PINS);

    // Call the bump task with the bumpData
    BumpTask(bumpData);

    // clear interrupt flags
    GPIO_clearInterruptFlag(BUMP_PORT, BUMP_PINS);


}
 */
