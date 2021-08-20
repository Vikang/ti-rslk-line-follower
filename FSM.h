#ifndef FSM_H_
#define FSM_H_

//#include "PortPins.h"
//#include "Switch.h"
#include <stdint.h>

// Type Definitions
typedef enum {
    Start,
    Bumped,
    Center,
    Slow,
    Left,
    Right,
    Lost,
    FarRight,
    FarLeft,
    FartherLeft,
    FartherRight
} FSMState;

typedef struct {
    FSMState     CurrentState;      // Current state of the FSM
    uint8_t CurrentLineInput;    // Current input of the FSM S1
    uint8_t CurrentBumpInput;    // Current input of the FSM S2
    int32_t CurrentDistance;    // Current input of the FSM S2
    uint8_t luxGood;
    uint8_t accelGood;
} FSMType;

// Function Prototypes
void InitializeFSM(FSMType *FSM);
FSMState NextStateFunction(FSMType *FSM);
void OutputFunction(FSMType *FSM);

#endif /* FSM_H_ */
