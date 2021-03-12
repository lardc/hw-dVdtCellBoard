// Header
#include "LowLevel.h"

// Functions
//
// LED on board
bool LL_IsBlinkLED()
{
	return GPIO_Read_Bit(GPIOB, Pin_12);
}
//-----------------------------

void LL_BlinkLED(bool State)
{
	State ? GPIO_Bit_Set(GPIOB, Pin_12) : GPIO_Bit_Rst(GPIOB, Pin_12);
}
//-----------------------------

// External LED
void LL_ExternalLED(bool State)
{
	State ? GPIO_Bit_Set(GPIOA, Pin_4) : GPIO_Bit_Rst(GPIOA, Pin_4);
}
//-----------------------------
