#ifndef __GLOBAL_H
#define __GLOBAL_H

// Include
#include "stdinc.h"

// Global parameters
//--------------------------------------------------------
#define	SCCI_TIMEOUT_TICKS				1000						// Receive timeout (in ms)
//
#define LED_BLINK_TIME					500
//
// Capacitor voltage parameters
#define CAP_VOLTAGE_MIN					50							// Capacitor minimum voltage (in V)
#define CAP_VOLTAGE_MAX					900							// Capacitor maximum voltage (in V)
#define ANALOG_REF_MV					5000						// (in mV)
#define ANALOG_REF_V					5							// (in V)
//
#define CAP_V_K							205							// Resistive chain divisor 1/CAP_V_K
#define CAP_V_RSHIFT					10							// div 1024
//
// Fine tuning
#define CAP_VF_N_MAX					1300
#define CAP_VF_N_MIN					700
#define CAP_VF_RSHIFT					10							// div 1024
//
// Voltage rate control
#define MAX_CELL_RATE					2000						// in V/us
//
// Regulator parameters
#define CAP_V_DEADZONE					2							// Regulator dead zone (in %)
#define CAP_V_DEADZONE_MIN_V			3							// Regulator dead zone min (in V)
#define CAP_V_DEADZONE_MAX_V			10							// Regulator dead zone max (in V)
#define CAP_V_WINDOW					3							// Acceptance window (in %)
#define CAP_V_WINDOW_MIN_V				5							// Acceptance window min (in V)
#define CAP_V_WINDOW_MAX_V				15							// Acceptance window max (in V)
//
// Duty part/PWM_TOP
#define FB_BASE_PWM_HIGH				500							// (in ticks)
#define FB_BASE_PWM_LOW					200							// (in ticks)
#define FB_BASE_PWM_IDLE				50							// 50 is about 1us (in ticks)
#define FB_BASE_PWM_ZONES				5							// Number of PWM zones
#define FB_BASE_PWM_ZONE_SIZE			((FB_BASE_PWM_HIGH - FB_BASE_PWM_LOW) / (FB_BASE_PWM_ZONES - 1))
#define BRK_BASE_PWM					200							// (in ticks)
//
// DAC = Vg * GATE_DAC_MAX / (Vref * Kgain)
// DAC = Vg * Kn / Kd
#define GATE_GAIN						1							// Output op-amp gain
#define GATE_V_N						GATE_DAC_MAX
#define GATE_V_D						(ANALOG_REF_MV * GATE_GAIN)
//
#define GATE_DAC_MAX					0x3ff						// DAC = 0..1023
//
#define GATE_VOLTAGE_MIN				0							// (in mV)
#define GATE_VOLTAGE_MAX				(ANALOG_REF_MV * GATE_GAIN)	// (in mV)
//--------------------------------------------------------

#define EP_WRITE_COUNT			0				// Количество массивов для записи
#define EP_COUNT				0				// Количество массивов для чтения
// Password to unlock non-volatile area for write
#define ENABLE_LOCKING			FALSE

#endif // __GLOBAL_H
