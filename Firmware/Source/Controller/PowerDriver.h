#ifndef __CAP_MON_H
#define __CAP_MON_H

// Include
#include "stdinc.h"

// Functions
//
// Set control mode
void DRIVER_SetMode(bool Activate);
// Set gate voltage
void DRIVER_SetGateVoltage(Int16U Voltage);
// Calculate gate voltage for chosen rate
Int16U DRIVER_CalculateVoltageByRate(Int16U Rate);
// Capacitor charger control routine
void DRIVER_ControlRoutine();
// Cache variables
void DRIVER_CacheVariables();
//
void DRIVER_SW_RateChannel(Int16U Voltage);
// Set flyback PWM
void FlybackPWMSet(uint16_t PWM_Value);
// Set Brake PWM
void BrakePWMSet(uint16_t PWM_Value);

#endif // __CAP_MON_H
