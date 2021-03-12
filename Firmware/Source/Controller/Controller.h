#ifndef CONTROLLER_H_
#define CONTROLLER_H_


// Includes
//
#include "../stdinc.h"


// Constants
//
typedef enum __DeviceState
{
	DS_None			= 0,
	DS_Fault		= 1,
	DS_Disabled		= 2,
	DS_Powered		= 3
} DeviceState;


// Variables
//
extern volatile long CONTROL_TimeCounterTemp;
extern volatile long CONTROL_TimeCounter;
extern volatile DeviceState CONTROL_State;


// Functions
//
// Initialize controller
void CONTROL_Init();
// Controller routine
void CONTROL_Cycle();
// Update low-priority states
void CONTROL_Idle();

#endif /* CONTROLLER_H_ */
