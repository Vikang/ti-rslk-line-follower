/* DriverLib Includes */
#include "driverlib.h"
#include "LaunchPad.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/* Project Includes */
#include "Clock.h"
#include "TimerA1.h"
#include "msp.h"
#include "Reflectance.h"
#include "Bump.h"
#include "PWM.h"
#include "Motor.h"
#include "Nokia5110.h"

#include "Booster_Pack/opt3001.h"
#include "Booster_Pack/i2c_driver.h"

//#include "CortexM.h"
#include "Booster_Pack/bmi160_support.h"
#include "Booster_Pack/bme280_support.h"
#include <math.h>

#include "FSM.h"
//#include "FSM2.h"

//global variables set by Reflectance.c and Bump.c
extern uint8_t result, bumpResult;
volatile int32_t location;

uint8_t data;

//Calibration off-sets
int8_t accel_off_x;
int8_t accel_off_y;
int8_t accel_off_z;
s16 gyro_off_x;
s16 gyro_off_y;
s16 gyro_off_z;

// BMI160
BMI160_RETURN_FUNCTION_TYPE returnValue;
struct bmi160_gyro_t        s_gyroXYZ;
struct bmi160_accel_t       s_accelXYZ;
struct bmi160_mag_xyz_s32_t s_magcompXYZ;
int returnRslt;

//BME
s32 g_s32ActualTemp   = 0;
u32 g_u32ActualPress  = 0;
u32 g_u32ActualHumity = 0;


#define X_LIMIT 4000 //1000
#define LUX_MED_LIMIT 3
#define LUX_HIGH_LIMIT 5

//some parameters on the light to duty conversion
//using a linear mapping of the range of light intensity to the range of duty cycles
//, and clamped output (aka max and min value for the speed)
#define MAX_SPEED 50 //fastest the robot will go, this number is based on 100 being the fatest
#define MIN_SPEED 0 //slowest the robot will go, 0 is a good number
#define MAX_LUX 4000 //point at which the robot speed is maximum
#define MIN_LUX 40 //minimum light for the robot to move

//equation is y=m*(x-x0)+y0
//where slope m = (MAX_SPEED-MIN_SPEED)/(MAX_LUX-MIN_LUX)
//x0 = MIN_LUX, y0 = MIN_SPEED
uint16_t lightToDuty(float lux){
    if (lux > MAX_LUX )return MAX_SPEED;
    if (lux < MIN_LUX) return MIN_SPEED;
    uint16_t duty = (uint16_t) ((MAX_SPEED-MIN_SPEED)*(lux-MIN_LUX)/(MAX_LUX-MIN_LUX));
    return duty;
}

void main (void){

    FSMType my_FSM;
    //initialize everything
    Clock_Init();
    Reflectance_Init();
    Bump_Init();
    LaunchPad_Init();
    PWM_Init(127,50,50);
    Motor_Init();
    Nokia5110_Init();

    //intialize i2c to communicate with booster pack
    initI2C();
    //Intialize opt3001 sensor
    sensorOpt3001Init();

    //Intialize BMI160 and BMM sensor
    bmi160_initialize_sensor();
    returnRslt = bmi160_config_running_mode(APPLICATION_NAVIGATION); //there are several modes to run the BMI sensor in
    bmi160_accel_foc_trigger_xyz(0x03, 0x03, 0x01, &accel_off_x, &accel_off_y, &accel_off_z);
    bmi160_set_foc_gyro_enable(0x01, &gyro_off_x, &gyro_off_y, &gyro_off_z);


    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN6 | GPIO_PIN7); // initializing brakelights as output pins
    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN0 | GPIO_PIN5); // initializing front lights as output pins

    InitializeFSM(&my_FSM);

    //initialize timer
    TimerA1_Init(999); // frequency is 1000Hz (1 ms)

    //determine which switch is being pressed
    while (1){
        data = LaunchPad_Input();
        if (data == 1){
            while(1){
                //reading OPT3001 sensor
                uint16_t rawData;
                float convertedLux;
                uint8_t luxGood;
                uint8_t accelGood;
                //Read and convert light values
                sensorOpt3001Read(&rawData);
                sensorOpt3001Convert(rawData, &convertedLux);

                if(convertedLux > LUX_HIGH_LIMIT){ //read the light value
                    //stop the motors
                    luxGood = 2;
                }
                else if(convertedLux > LUX_MED_LIMIT) {
                    luxGood = 1;
                }
                else{
                    luxGood = 0; //no light
                }

                //acceleration
                bmi160_read_accel_xyz(&s_accelXYZ); //read the acceleration value
                if(s_accelXYZ.x > X_LIMIT | s_accelXYZ.y > X_LIMIT | s_accelXYZ.y < -1*X_LIMIT | s_accelXYZ.x < X_LIMIT*-1){
                    accelGood = 0;
                } else{
                    accelGood = 1;
                }

                //Read current input
                my_FSM.CurrentBumpInput = bumpResult;
                my_FSM.CurrentLineInput = (result & 0x18) >> 3;
                my_FSM.CurrentDistance = Reflectance_Position(result);
                my_FSM.luxGood = luxGood;
                my_FSM.accelGood = accelGood;

                //Using input value and current state, determine next state
                my_FSM.CurrentState = NextStateFunction(&my_FSM);

                //Produce outputs based on current state
                OutputFunction(&my_FSM);
            }
        }
    }
}
