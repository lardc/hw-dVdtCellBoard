#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "ZwGPIO.h"


// Functions
//
void LL_ToggleLed();
void LL_ExternalLED(bool State);
void LL_SW_I_LIM(bool State);
void LL_SW_LOW_RATE_CHNNL(bool State);
void LL_SW_MID_RATE_CHNNL(bool State);
void LL_SW_HIGH_RATE_CHNNL(bool State);

#endif //__LOWLEVEL_H
