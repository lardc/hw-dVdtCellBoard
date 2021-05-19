#ifndef __GLOBAL_H
#define __GLOBAL_H

// Include
#include "stdinc.h"

// Global parameters
#define	SCCI_TIMEOUT_TICKS				1000	// Receive timeout (in ms)
#define EP_WRITE_COUNT					0		// Количество массивов для записи
#define EP_COUNT						0		// Количество массивов для чтения
#define ENABLE_LOCKING					FALSE
#define LED_BLINK_TIME					500		// (in ms)

// TIM mask
#define PWM_OUT_LOW_POL					0xFFFD

// Capacitor voltage parameters
#define CAP_VOLTAGE_MIN					50		// Capacitor minimum voltage (in V)
#define CAP_VOLTAGE_MAX					900		// Capacitor maximum voltage (in V)
#define ANALOG_REF_MV					3300	// (in mV)
#define ADC_RESOLUTION					4095

// Fine tuning
#define CAP_VF_N_MAX					1300
#define CAP_VF_N_MIN					700
#define CAP_VF_RSHIFT					10		// div 1024

// Regulator parameters
#define CAP_V_DEADZONE					2		// Regulator dead zone (in %)
#define CAP_V_DEADZONE_MIN_V			3		// Regulator dead zone min (in V)
#define CAP_V_DEADZONE_MAX_V			10		// Regulator dead zone max (in V)
#define CAP_V_WINDOW					3		// Acceptance window (in %)
#define CAP_V_WINDOW_MIN_V				5		// Acceptance window min (in V)
#define CAP_V_WINDOW_MAX_V				15		// Acceptance window max (in V)

// Duty part/PWM_TOP
#define FB_BASE_PWM_HIGH				500		// (in ticks)
#define FB_BASE_PWM_LOW					200		// (in ticks)
#define FB_BASE_PWM_IDLE				50		// 50 is about 1us (in ticks)
#define FB_BASE_PWM_ZONES				5		// Number of PWM zones
#define FB_BASE_PWM_ZONE_SIZE			((FB_BASE_PWM_HIGH - FB_BASE_PWM_LOW) / (FB_BASE_PWM_ZONES - 1))
#define BRK_BASE_PWM					200		// (in ticks)

// DAC settings
#define GATE_DAC_MAX					4095

#endif // __GLOBAL_H
