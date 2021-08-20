#include "FSM.h"
#include "Clock.h"
#include "GPIO.h"
#include <stdio.h>
#include "Motor.h"
#include "PWM.h"
#include "Nokia5110.h"

//--------------------------------------------------------------------------
// Initialize FSM
//--------------------------------------------------------------------------
void InitializeFSM(FSMType *FSM)
{
    FSM->CurrentState = Start;
}

//--------------------------------------------------------------------------
// Determine next FSM state
//--------------------------------------------------------------------------
FSMState NextStateFunction(FSMType *FSM)
{
    FSMState NextState = FSM->CurrentState;

    switch (FSM->CurrentState){
//--Heart Beating states----------------------------------------------------
    case Start:
        if(FSM->CurrentBumpInput > 0){
            NextState = Bumped;
        }
        else if (FSM->luxGood == 0){
            NextState = Bumped;
        }
        else if (FSM->accelGood == 0){
            NextState = Bumped;
        }
        else if(FSM->luxGood == 1 && FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
            NextState = Slow;
        }
        else if (FSM->CurrentDistance > 95 && FSM->CurrentDistance < 142){
            NextState = FartherRight;
        }
        else if (FSM->CurrentDistance < -95 && FSM->CurrentDistance > -142){
            NextState = FartherLeft;
        }
        else if (FSM->CurrentDistance == 142){
            NextState = FarRight;
        }
        else if (FSM->CurrentDistance == -142){
            NextState = FarLeft;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
            NextState = Center;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 2){
            NextState = Left;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 1){
            NextState = Right;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 0){
            NextState = Lost;
        }
        else{
            NextState = Start;
        }
        break;

    case Slow:
        if(FSM->CurrentBumpInput > 0){
            NextState = Bumped;
        }
        else if (FSM->luxGood == 0){
            NextState = Bumped;
        }
        else if (FSM->accelGood == 0){
            NextState = Bumped;
        }
        else if(FSM->luxGood == 1 && FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
            NextState = Slow;
        }
        else if (FSM->CurrentDistance > 95 && FSM->CurrentDistance < 142){
            NextState = FartherRight;
        }
        else if (FSM->CurrentDistance < -95 && FSM->CurrentDistance > -142){
            NextState = FartherLeft;
        }
        else if (FSM->CurrentDistance == 142){
            NextState = FarRight;
        }
        else if (FSM->CurrentDistance == -142){
            NextState = FarLeft;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
            NextState = Center;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 2){
            NextState = Left;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 1){
            NextState = Right;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 0){
            NextState = Lost;
        }
        else{
            NextState = Slow;
        }
        break;

    case Bumped:
        if(FSM->CurrentBumpInput > 0){
            NextState = Bumped;
        }
        else if (FSM->luxGood == 0){
            NextState = Bumped;
        }
        else if (FSM->accelGood == 0){
            NextState = Bumped;
        }
        else if(FSM->luxGood == 1 && FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
            NextState = Slow;
        }
        else if (FSM->CurrentDistance > 95 && FSM->CurrentDistance < 142){
            NextState = FartherRight;
        }
        else if (FSM->CurrentDistance < -95 && FSM->CurrentDistance > -142){
            NextState = FartherLeft;
        }
        else if (FSM->CurrentDistance == 142){
            NextState = FarRight;
        }
        else if (FSM->CurrentDistance == -142){
            NextState = FarLeft;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
            NextState = Center;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 2){
            NextState = Left;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 1){
            NextState = Right;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 0){
            NextState = Lost;
        }
        else{
            NextState = Bumped;
        }
        break;

    case Center:
        if(FSM->CurrentBumpInput > 0){
            NextState = Bumped;
        }
        else if (FSM->luxGood == 0){
            NextState = Bumped;
        }
        else if (FSM->accelGood == 0){
            NextState = Bumped;
        }
        else if(FSM->luxGood == 1 && FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
            NextState = Slow;
        }
        else if (FSM->CurrentDistance > 95 && FSM->CurrentDistance < 142){
            NextState = FartherRight;
        }
        else if (FSM->CurrentDistance < -95 && FSM->CurrentDistance > -142){
            NextState = FartherLeft;
        }
        else if (FSM->CurrentDistance == 142){
            NextState = FarRight;
        }
        else if (FSM->CurrentDistance == -142){
            NextState = FarLeft;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
            NextState = Center;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 2){
            NextState = Left;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 1){
            NextState = Right;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 0){
            NextState = Lost;
        }
        else{
            NextState = Center;
        }
        break;

    case Left:
        if(FSM->CurrentBumpInput > 0){
            NextState = Bumped;
        }
        else if (FSM->luxGood == 0){
            NextState = Bumped;
        }
        else if (FSM->accelGood == 0){
            NextState = Bumped;
        }
        else if(FSM->luxGood == 1 && FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
            NextState = Slow;
        }
        else if (FSM->CurrentDistance > 95 && FSM->CurrentDistance < 142){
            NextState = FartherRight;
        }
        else if (FSM->CurrentDistance < -95 && FSM->CurrentDistance > -142){
            NextState = FartherLeft;
        }
        else if (FSM->CurrentDistance == 142){
            NextState = FarRight;
        }
        else if (FSM->CurrentDistance == -142){
            NextState = FarLeft;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
            NextState = Center;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 2){
            NextState = Left;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 1){
            NextState = Right;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 0){
            NextState = Lost;
        }
        else{
            NextState = Left;
        }
        break;

    case Right:
        if(FSM->CurrentBumpInput > 0){
            NextState = Bumped;
        }
        else if (FSM->luxGood == 0){
            NextState = Bumped;
        }
        else if (FSM->accelGood == 0){
            NextState = Bumped;
        }
        else if(FSM->luxGood == 1 && FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
            NextState = Slow;
        }
        else if (FSM->CurrentDistance > 95 && FSM->CurrentDistance < 142){
            NextState = FartherRight;
        }
        else if (FSM->CurrentDistance < -95 && FSM->CurrentDistance > -142){
            NextState = FartherLeft;
        }
        else if (FSM->CurrentDistance == 142){
            NextState = FarRight;
        }
        else if (FSM->CurrentDistance == -142){
            NextState = FarLeft;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
            NextState = Center;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 2){
            NextState = Left;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 1){
            NextState = Right;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 0){
            NextState = Lost;
        }
        else{
            NextState = Right;
        }
        break;

    case Lost:
        if(FSM->CurrentBumpInput > 0){
            NextState = Bumped;
        }
        else if (FSM->luxGood == 0){
            NextState = Bumped;
        }
        else if (FSM->accelGood == 0){
            NextState = Bumped;
        }
        else if(FSM->luxGood == 1 && FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
            NextState = Slow;
        }
        else if (FSM->CurrentDistance > 95 && FSM->CurrentDistance < 142){
            NextState = FartherRight;
        }
        else if (FSM->CurrentDistance < -95 && FSM->CurrentDistance > -142){
            NextState = FartherLeft;
        }
        else if (FSM->CurrentDistance == 142){
            NextState = FarRight;
        }
        else if (FSM->CurrentDistance == -142){
            NextState = FarLeft;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
            NextState = Center;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 2){
            NextState = Left;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 1){
            NextState = Right;
        }
        else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 0){
            NextState = Lost;
        }
        else{
            NextState = Lost;
        }
        break;

    case FarRight:
            if(FSM->CurrentBumpInput > 0){
                NextState = Bumped;
            }
            else if (FSM->luxGood == 0){
                NextState = Bumped;
            }
            else if (FSM->accelGood == 0){
                NextState = Bumped;
            }
            else if(FSM->luxGood == 1 && FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
                NextState = Slow;
            }
            else if (FSM->CurrentDistance > 95 && FSM->CurrentDistance < 142){
                NextState = FartherRight;
            }
            else if (FSM->CurrentDistance < -95 && FSM->CurrentDistance > -142){
                NextState = FartherLeft;
            }
            else if (FSM->CurrentDistance == 142){
                NextState = FarRight;
            }
            else if (FSM->CurrentDistance == -142){
                NextState = FarLeft;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
                NextState = Center;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 2){
                NextState = Left;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 1){
                NextState = Right;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 0){
                NextState = Lost;
            }
            else{
                NextState = FarRight;
            }
            break;

    case FarLeft:
            if(FSM->CurrentBumpInput > 0){
                NextState = Bumped;
            }
            else if (FSM->luxGood == 0){
                NextState = Bumped;
            }
            else if (FSM->accelGood == 0){
                NextState = Bumped;
            }
            else if(FSM->luxGood == 1 && FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
                NextState = Slow;
            }
            else if (FSM->CurrentDistance > 95 && FSM->CurrentDistance < 142){
                NextState = FartherRight;
            }
            else if (FSM->CurrentDistance < -95 && FSM->CurrentDistance > -142){
                NextState = FartherLeft;
            }
            else if (FSM->CurrentDistance == 142){
                NextState = FarRight;
            }
            else if (FSM->CurrentDistance == -142){
                NextState = FarLeft;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
                NextState = Center;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 2){
                NextState = Left;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 1){
                NextState = Right;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 0){
                NextState = Lost;
            }
            else{
                NextState = FarLeft;
            }
            break;

    case FartherRight:
            if(FSM->CurrentBumpInput > 0){
                NextState = Bumped;
            }
            else if (FSM->luxGood == 0){
                NextState = Bumped;
            }
            else if (FSM->accelGood == 0){
                NextState = Bumped;
            }
            else if(FSM->luxGood == 1 && FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
                NextState = Slow;
            }
            else if (FSM->CurrentDistance > 95 && FSM->CurrentDistance < 142){
                NextState = FartherRight;
            }
            else if (FSM->CurrentDistance < -95 && FSM->CurrentDistance > -142){
                NextState = FartherLeft;
            }
            else if (FSM->CurrentDistance == 142){
                NextState = FarRight;
            }
            else if (FSM->CurrentDistance == -142){
                NextState = FarLeft;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
                NextState = Center;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 2){
                NextState = Left;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 1){
                NextState = Right;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 0){
                NextState = Lost;
            }
            else{
                NextState = FartherRight;
            }
            break;

    case FartherLeft:
            if(FSM->CurrentBumpInput > 0){
                NextState = Bumped;
            }
            else if (FSM->luxGood == 0){
                NextState = Bumped;
            }
            else if (FSM->accelGood == 0){
                NextState = Bumped;
            }
            else if(FSM->luxGood == 1 && FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
                NextState = Slow;
            }
            else if (FSM->CurrentDistance > 95 && FSM->CurrentDistance < 142){
                NextState = FartherRight;
            }
            else if (FSM->CurrentDistance < -95 && FSM->CurrentDistance > -142){
                NextState = FartherLeft;
            }
            else if (FSM->CurrentDistance == 142){
                NextState = FarRight;
            }
            else if (FSM->CurrentDistance == -142){
                NextState = FarLeft;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 3){
                NextState = Center;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 2){
                NextState = Left;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 1){
                NextState = Right;
            }
            else if(FSM->CurrentBumpInput == 0 && FSM->CurrentLineInput == 0){
                NextState = Lost;
            }
            else{
                NextState = FartherLeft;
            }
            break;
    }


    return NextState;
}

//--------------------------------------------------------------------------
// Determine LED output based on state
//--------------------------------------------------------------------------


void OutputFunction(FSMType *FSM)
{
    switch (FSM->CurrentState) {
    case Start:
        //do nothing, we dont know which state we're in yet
        break;
    case Slow:
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6 | GPIO_PIN7); //turn OFF back pins
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0 | GPIO_PIN5);// turn ON front pins
        Motor_Forward(15,15);

        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("SLOW");
        Nokia5110_SetCursor(0, 3);
        Nokia5110_OutString("ZZZ");
        break;
    case Bumped:
        //turn on all LEDs when bumped
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN6 | GPIO_PIN7); //turn ON back pins
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0 | GPIO_PIN5);// turn ON front pins
        Motor_Stop();

        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("STOP");
        Nokia5110_SetCursor(0, 3);
        Nokia5110_OutString("!!!");
        break;
    case Center:
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6 | GPIO_PIN7); //turn OFF back pins
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0 | GPIO_PIN5);// turn ON front pins
        Motor_Forward(30,30);

        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("CENTER");
        Nokia5110_SetCursor(0, 3);
        Nokia5110_OutString("^^");
        break;
    case Left:
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6 | GPIO_PIN7); //turn OFF back pins
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0); //turn OFF front right pin
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5);// turn ON front left pin
        Motor_Left(15,15);

        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("LEFT");
        Nokia5110_SetCursor(0, 3);
        Nokia5110_OutString("->");
        break;
    case Right:
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6 | GPIO_PIN7); //turn OFF back pins
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN5); //turn OFF front left pin
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);// turn ON front right pin
        Motor_Right(15,15);

        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("RIGHT");
        Nokia5110_SetCursor(0, 3);
        Nokia5110_OutString("<-");
        break;
    case Lost:
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0 | GPIO_PIN5); // turn OFF front pins
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN6 | GPIO_PIN7);//turn ON back pins
        //Motor_Stop();
        Motor_Right(15,15);

        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("LOST");
        Nokia5110_SetCursor(0, 3);
        Nokia5110_OutString("???");
        break;
    case FarRight:
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6 | GPIO_PIN7); //turn OFF back pins
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN5); //turn OFF front left pin
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);// turn ON front right pin
        Motor_Right(50,50);
        Clock_Delay1ms(100);

        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("FAR RIGHT");
        Nokia5110_SetCursor(0, 3);
        Nokia5110_OutString("<---");
        break;

    case FarLeft:
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6 | GPIO_PIN7); //turn OFF back pins
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0); //turn OFF front right pin
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5);// turn ON front left pin
        Motor_Left(50,50);
        Clock_Delay1ms(100);

        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("FAR LEFT");
        Nokia5110_SetCursor(0, 3);
        Nokia5110_OutString("--->");
        break;

    case FartherRight:
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6 | GPIO_PIN7); //turn OFF back pins
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN5); //turn OFF front left pin
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);// turn ON front right pin
        Motor_Forward(10,10);
        Clock_Delay1ms(400);
        Motor_Right(60,60);
        Clock_Delay1ms(200);

        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("FAR RIGHT");
        Nokia5110_SetCursor(0, 3);
        Nokia5110_OutString("<---");
        break;

    case FartherLeft:
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6 | GPIO_PIN7); //turn OFF back pins
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0); //turn OFF front right pin
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5);// turn ON front left pin
        Motor_Forward(10,10);
        Clock_Delay1ms(400);
        Motor_Left(60,60);
        Clock_Delay1ms(200);

        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("FAR LEFT");
        Nokia5110_SetCursor(0, 3);
        Nokia5110_OutString("--->");
        break;

    }


}
