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

// I_LIM
void LL_SW_I_LIM(bool State)
{
	GPIO_SetState(GPIO_I_LIM, State);
}
//-----------------------------

void LL_SW_LOW_RATE_CHNNL(bool State)
{
	GPIO_SetState(GPIO_LOW_RATE_CHNNL, State);
}
//-----------------------------

void LL_SW_MID_RATE_CHNNL(bool State)
{
	GPIO_SetState(GPIO_MID_RATE_CHNNL, State);
}
//-----------------------------

void LL_SW_HIGH_RATE_CHNNL(bool State)
{
	GPIO_SetState(GPIO_HIGH_RATE_CHNNL, State);
}
//-----------------------------
