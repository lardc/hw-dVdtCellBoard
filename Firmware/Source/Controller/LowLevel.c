// Header
#include "LowLevel.h"
#include "Board.h"

// Functions
//
// LED on board
void LL_ToggleLed()
{
	GPIO_Toggle(GPIO_LED2);
}
//-----------------------------

// External LED
void LL_ExternalLED(bool State)
{
	GPIO_SetState(GPIO_LED1, State);
}
//-----------------------------
