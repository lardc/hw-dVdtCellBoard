#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "ZwGPIO.h"


// Functions
//
bool LL_IsBlinkLED();
void LL_BlinkLED(bool State);
void LL_ExternalLED(bool State);

#endif //__LOWLEVEL_H
