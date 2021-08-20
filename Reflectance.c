#include <stdint.h>
/*
 * Reflectance.c
 * Provides functions to
 * 1. Initialize Pololu reflectance sensor
 * 2. Read Pololu reflectance sensor
 * 3. Determine robot position
 * 4. Determine robot status
 *
 */

//we include "GPIO.h" so we can use the driver library functions
#include "GPIO.h"
#include <stdio.h>

#include "Clock.h"
#include "Reflectance.h"

#define ALLBITS  0xFF
#define BITSHIFT 0x01

uint8_t result;

//------------Reflectance_Init------------
// Initialize sensor array to GPIO, set LEDs (P5.3 and P9.2) 
// as output and sensors (P7.0-P7.7) as output
// Input: none
// Output: none
void Reflectance_Init(void){
    //Setting LEDs (P5.3 and P9.2) as output and as low
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setAsOutputPin(GPIO_PORT_P9, GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN2);

    //Setting Sensors (P7.0-P7.7) as output
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN3);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN5);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN7);
}

void Reflectance_Start(){

    // 1. Turn on even and odd LEDs
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setOutputHighOnPin(GPIO_PORT_P9, GPIO_PIN2);
    // 2. Charge reflectance sensor capacitors (set as output and high on P7.0-P7.7)
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN3);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN5);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN7);

    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN0);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN1);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN3);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN4);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN5);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN6);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN7);


    // 3. Wait 10us for capacitors to charge
    Clock_Delay1us(10);

    // 4. Set reflectance sensor (P7.0-P7.7) as input
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN0);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN1);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN2);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN3);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN4);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN5);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN6);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN7);

    //printf ("%s \n", "START");
}

uint8_t Reflectance_End(void){

    // 6. Read reflectance sensor values and assign to result
    //uint8_t result;

    // Here we get each pin value and assign it to a variable for ease of use later
    uint8_t val0 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN0);
    uint8_t val1 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN1);
    uint8_t val2 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN2);
    uint8_t val3 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN3);
    uint8_t val4 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN4);
    uint8_t val5 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN5);
    uint8_t val6 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN6);
    uint8_t val7 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN7);

    //One by one the "result" which is our 8 bit value is built. This is done by bit shifting each value in place.
    result = val7 << 7;
    result |= val6 << 6;
    result |= val5 << 5;
    result |= val4 << 4;
    result |= val3 << 3;
    result |= val2 << 2;
    result |= val1 << 1;
    result |= val0;

    // 8. Turn off the LEDs
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN2);
    //printf ("%s \n", "END");

    //printf("value: %d\n", result);

    return result;
}

void Reflectance_Test(void){
    printf ("%s \n", "BUMP");
}


//------------Reflectance_Read------------
// Read reflectance sensor
// Input: the delay time in us
// Output: result the sensor readings, bit 0 corresponds
//         to the rightmost sensor, bit 7 to the leftmost sensor
uint8_t Reflectance_Read(uint32_t time){
    // 1. Turn on even and odd LEDs
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setOutputHighOnPin(GPIO_PORT_P9, GPIO_PIN2);
    // 2. Charge reflectance sensor capacitors (set as output and high on P7.0-P7.7)
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN3);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN5);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN7);

    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN0);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN1);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN3);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN4);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN5);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN6);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN7);


    // 3. Wait 10us for capacitors to charge
    Clock_Delay1us(10);

    // 4. Set reflectance sensor (P7.0-P7.7) as input
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN0);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN1);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN2);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN3);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN4);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN5);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN6);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN7);

    // 5. Wait @param time
    Clock_Delay1us(time);

    // 6. Read reflectance sensor values and assign to result
    uint8_t result;

    // Here we get each pin value and assign it to a variable for ease of use later
    uint8_t val0 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN0);
    uint8_t val1 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN1);
    uint8_t val2 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN2);
    uint8_t val3 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN3);
    uint8_t val4 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN4);
    uint8_t val5 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN5);
    uint8_t val6 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN6);
    uint8_t val7 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN7);

    //One by one the "result" which is our 8 bit value is built. This is done by bit shifting each value in place.
    result = val7 << 7;
    result |= val6 << 6;
    result |= val5 << 5;
    result |= val4 << 4;
    result |= val3 << 3;
    result |= val2 << 2;
    result |= val1 << 1;
    result |= val0;

    // 8. Turn off the LEDs
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN2);

    return result;

}


//------------Reflectance_Center------------
// Determine robot's status over the line
// Input: the delay time in us
// Output: result the robot location status (LOST/RIGHT/LEFT/ON LINE)
uint8_t Reflectance_Center(uint32_t time){
    //Get reflectance read data
    uint8_t data = Reflectance_Read(time);
    //Here we get the left center and right center values by masking 0x18 (00011000) and right shifting by 3.
    //This will return 3 for if its centered, 2 if left of line, 1 if right of line, and 0 if lost.
    uint8_t center = (data & 0x18) >> 3;

    return center;
    
    /* Check robot status truth table
     * INPUT (L,R) | OUTPUT
     * ------------|------------
     *      11     | ON_LINE (3)
     *      10     | LEFT    (2)
     *      01     | RIGHT   (1)
     *      00     | LOST    (0)
     */

}

//------------Reflectance_Position------------
// Determine robot's status over the line
// Input: the collected sensor data 
// Output: the position value between +345 (most left)
//         to -345 (most right)
int32_t Reflectance_Position(uint8_t data){
    //Set up weight vector in an array
    int W_i[] = {334, 238, 142, 48, -48, -142, -238, -334};

    //initialize variables
    int total = 0;
    int counter = 0;
    int value = 0;
    int i;

    // for each bit value in data
    for(i = 0; i < 8; i++ ){
        //extract a bit into "value" varaible
          value = (data >> i) & 0x01;
          //if the bit is a 1, add to total and counter
          if (value != 0){
              total += W_i[i];
              counter ++;
          }
       }
    //return the distance of the center of the sensor to the center of the line
    return total / counter;
 
}

