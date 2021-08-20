#include "driverlib.h"
#include "PWM.h"
#include "Motor.h"

//   Left Motor:                Right Motor:
//    - Direction: P5.4         - Direction: P5.5
//    - PWM:       P2.7         - PWM        P2.6
//    - Enable:    P3.7         - Enable     P3.6

void Motor_Init(void){
    // initialize PWM outputs to 0% duty cycle on the two motor PWM pins (P2.6 and P2.7)
    PWM_Duty_Right(0);
    PWM_Duty_Left(0);
    // initialize motor enable and direction pins as GPIO outputs
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN6 | GPIO_PIN7); // enable pins
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN4 | GPIO_PIN5); // direction pins
    // set motors to sleep mode
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN6 | GPIO_PIN7); // HIGH = sleep OFF , LOW = sleep on
    // set motor direction to forward initially
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4 | GPIO_PIN5); // LOW = forward, HIGH = Backward
}


// Drive both motors forwards at the given duty cycles
void Motor_Forward(uint16_t leftDuty, uint16_t rightDuty){
    GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN6 | GPIO_PIN7); //enable
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4 | GPIO_PIN5); // go forward
    // turn right and left motors based on duty
    PWM_Duty_Right(rightDuty);
    PWM_Duty_Left(leftDuty);
}


// Drive both motors backwards at the given duty cycles
void Motor_Backward(uint16_t leftDuty, uint16_t rightDuty){
    GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN6 | GPIO_PIN7); //enable
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN4 | GPIO_PIN5); // go backward
    // turn right and left motors based on duty
    PWM_Duty_Right(rightDuty);
    PWM_Duty_Left(leftDuty);
}


// Drive the right motor forwards and the left motor backwards at the given duty cycles
void Motor_Left(uint16_t leftDuty, uint16_t rightDuty){
    GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN6 | GPIO_PIN7); //enable
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN5); // right forward
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN4); // left backwards
    // turn right and left motors based on duty
    PWM_Duty_Right(rightDuty);
    PWM_Duty_Left(leftDuty);

}


// Drive the right motor backwards and the left motor forwards at the given duty cycles
void Motor_Right(uint16_t leftDuty, uint16_t rightDuty){
    GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN6 | GPIO_PIN7); // enable
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN5); // right backwards
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4); // left forwards
    // turn right and left motors based on duty
    PWM_Duty_Right(rightDuty);
    PWM_Duty_Left(leftDuty);
}


// Stop the motors and enter sleep mode
void Motor_Stop(void){
    //stop motors
    PWM_Duty_Right(0);
    PWM_Duty_Left(0);
    //enter sleep mode
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN6 | GPIO_PIN7);


}
