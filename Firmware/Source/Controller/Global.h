#ifndef __GLOBAL_H
#define __GLOBAL_H

// Include
#include "stdinc.h"

// Global parameters
#define	SCCI_TIMEOUT_TICKS				1000	// Receive timeout (in ms)
#define EP_WRITE_COUNT					0		// ���������� �������� ��� ������
#define EP_COUNT						0		// ���������� �������� ��� ������
#define ENABLE_LOCKING					FALSE
#define LED_BLINK_TIME					500		// (in ms)

// TIM mask
#define PWM_OUT_LOW_POL					0xFFFD

// ADC & DAC settings
#define ANALOG_REF_MV					3300	// (in mV)
#define ADC_DAC_RESOLUTION				4095

// Fine tuning
#define CAP_V_CONV						0.319f

// Regulator parameters
#define CAP_V_DEADZONE					2		// Regulator dead zone (in %)
#define CAP_V_DEADZONE_MIN_V			3		// Regulator dead zone min (in V)
#define CAP_V_DEADZONE_MAX_V			10		// Regulator dead zone max (in V)
#define CAP_V_WINDOW					3		// Acceptance window (in %)
#define CAP_V_WINDOW_MIN_V				5		// Acceptance window min (in V)
#define CAP_V_WINDOW_MAX_V				15		// Acceptance window max (in V)

// Duty part
#define FB_BASE_PWM_HIGH				500		// (in ticks)
#define FB_BASE_PWM_LOW					200		// (in ticks)
#define FB_BASE_PWM_IDLE				50		// 50 is about 1us (in ticks)
#define FB_BASE_PWM_ZONES				5		// Number of PWM zones
#define FB_BASE_PWM_ZONE_SIZE			((FB_BASE_PWM_HIGH - FB_BASE_PWM_LOW) / (FB_BASE_PWM_ZONES - 1))
#define BRK_BASE_PWM					3890	// (in ticks)
#define BRK_TOP_PWM						4095

// Gate voltage settings
#define GATE_ANALOG_GAIN				1.42f

#endif // __GLOBAL_H
