// Includes
#include "PowerDriver.h"
//
#include <stdlib.h>
//
#include "../Platform/DeviceObjectDictionary.h"
#include "../Platform/DataTable.h"
#include "Global.h"
#include "Board.h"
#include "SysConfig.h"
#include "Measurement.h"
#include "LowLevel.h"

// Variables
//
static bool Shutdown = FALSE;
static volatile bool Active = FALSE;
static volatile bool hystOn = FALSE;
static char ErrorLimit = CAP_V_DEADZONE_MIN_V;
static char AcceptableWindow = CAP_V_WINDOW_MIN_V;
static Int16U Correction = (1 << CAP_VF_RSHIFT);
static Int16U DesiredVoltage = CAP_VOLTAGE_MIN;


// Forward functions
char DRIVER_CalculateVoltageSaturated(Int8U Percent, Int8U LowSat, Int8U HighSat);
Int16U DRIVER_ValueSaturate(Int16U Var, Int16U LowSat, Int16U HighSat);

// Functions
//
void DRIVER_SetMode(bool Activate)
{
	Active = Activate;
}

char DRIVER_CalculateVoltageSaturated(Int8U Percent, Int8U LowSat, Int8U HighSat)
{
	Int16U t = ((Int16U)Percent) * DataTable[REG_DESIRED_VOLTAGE] / 100;
	return DRIVER_ValueSaturate(t, LowSat, HighSat);
}

Int16U DRIVER_ValueSaturate(Int16U Var, Int16U LowSat, Int16U HighSat)
{
	if (Var < LowSat)
		Var = LowSat;
	else if (Var > HighSat)
		Var = HighSat;
	
	return Var;
}

void DRIVER_CacheVariables()
{
	ErrorLimit = DRIVER_CalculateVoltageSaturated(CAP_V_DEADZONE, CAP_V_DEADZONE_MIN_V, CAP_V_DEADZONE_MAX_V);
	AcceptableWindow = DRIVER_CalculateVoltageSaturated(CAP_V_WINDOW, CAP_V_WINDOW_MIN_V, CAP_V_WINDOW_MAX_V);
	
	Correction = DRIVER_ValueSaturate(DataTable[REG_VOLTAGE_FINE_N], CAP_VF_N_MIN, CAP_VF_N_MAX);
	DesiredVoltage = DRIVER_ValueSaturate(DataTable[REG_DESIRED_VOLTAGE], CAP_VOLTAGE_MIN, CAP_VOLTAGE_MAX);
}

void DRIVER_SW_RateChannel(Int16U Voltage)
{
	LL_SW_LOW_RATE_CHNNL(false);
	LL_SW_MID_RATE_CHNNL(false);
	LL_SW_HIGH_RATE_CHNNL(false);

	//if (Voltage <= LOW_RATE)
	//{
	//	LL_SW_LOW_RATE_CHNNL(true);
	//	LL_SW_MID_RATE_CHNNL(false);
	//	LL_SW_HIGH_RATE_CHNNL(false);
	//}

	//else if (Voltage <= MID_RATE)
	//{
	//	LL_SW_LOW_RATE_CHNNL(false);
	//	LL_SW_MID_RATE_CHNNL(true);
	//	LL_SW_HIGH_RATE_CHNNL(false);
	//}

	//else
	//{
		LL_SW_LOW_RATE_CHNNL(false);
		LL_SW_MID_RATE_CHNNL(false);
		LL_SW_HIGH_RATE_CHNNL(true);
	//}
}

void DRIVER_SetGateVoltage(Int16U Voltage)
{
	Int16U val;
	Int16U result;

	//if (Voltage <= LOW_RATE)
	//{
	//	val = (Int16U)((float)Voltage / LOW_RATE * ANALOG_REF_MV);
	//}
	//else if (Voltage <= MID_RATE)
	//{
	//	val = (Int16U)((float)Voltage / MID_RATE * ANALOG_REF_MV);
	//}
	//else
	//{
		val = (Int16U)((float)Voltage / HIGH_RATE * ANALOG_REF_MV);
	//}
	
	result = (((Int16U)val) * GATE_V_N) / GATE_V_D;

	// Saturate value
	if(result > GATE_DAC_MAX) result = GATE_DAC_MAX;

	// Set gate voltage
	DAC_SetValueCh1(DAC1, result);
}

void DRIVER_ControlRoutine()
{
	Int16U pwm_fb, ActualVoltage;
	Int8U pwm_fb_sleep;
	float capV;

	capV = MEASURE_SingleSampleBatteryVoltage();
	DataTable[REG_ACTUAL_VOLTAGE] = (Int16U)capV;
	ActualVoltage = capV;

	if(Active)
	{
		int err = DesiredVoltage - ActualVoltage;
		
		// Select proper PWM duty cycle
		if (ActualVoltage < 200)
		{
			pwm_fb = FB_BASE_PWM_LOW;
			pwm_fb_sleep = FB_BASE_PWM_IDLE;
		}
		else if (ActualVoltage < 400)
		{
			pwm_fb = FB_BASE_PWM_LOW + FB_BASE_PWM_ZONE_SIZE;
			pwm_fb_sleep = FB_BASE_PWM_IDLE;
		}
		else if (ActualVoltage < 600)
		{
			pwm_fb = FB_BASE_PWM_LOW + FB_BASE_PWM_ZONE_SIZE * 2;
			pwm_fb_sleep = FB_BASE_PWM_IDLE * 2;
		}
		else if (ActualVoltage < 800)
		{
			pwm_fb = FB_BASE_PWM_LOW + FB_BASE_PWM_ZONE_SIZE * 3;
			pwm_fb_sleep = FB_BASE_PWM_IDLE * 3;
		}
		else
		{
			pwm_fb = FB_BASE_PWM_HIGH;
			pwm_fb_sleep = FB_BASE_PWM_IDLE * 4;
		}
		
		// Override startup PWM
		if (ActualVoltage < 30) pwm_fb = FB_BASE_PWM_IDLE;

		if(err >= ErrorLimit)
		{
			// active charge zone
			hystOn = TRUE;
			FlybackPWMSet(pwm_fb);
			BrakePWMSet(0);
		}
		else if(err <= -(ErrorLimit * 2))
		{
			// active discharge zone
			hystOn = FALSE;
			FlybackPWMSet(0);
			BrakePWMSet(BRK_BASE_PWM);
		}
		else if(err <= -ErrorLimit)
		{
			// soft self-discharge zone
			hystOn = FALSE;
			FlybackPWMSet(0);
			BrakePWMSet(0);
		}
		else
		{
			// soft charge zone
			FlybackPWMSet(hystOn ? pwm_fb_sleep : 0);
			BrakePWMSet(0);
		}

		DataTable[REG_VOLTAGE_OK] = (labs(err) < AcceptableWindow) ? 1 : 0;
		Shutdown = FALSE;
	}
	else
	{
		if(!Shutdown)
		{
			FlybackPWMSet(0);
			BrakePWMSet(PWM_TOP_LOW);

			DataTable[REG_VOLTAGE_OK] = 0;
			Shutdown = TRUE;
		}
	}
}

void FlybackPWMSet(uint16_t PWM_Value)
{
	TIM15_16_17_PWM_CH1_SetValue(TIM15, PWM_Value);
}

void BrakePWMSet(uint16_t PWM_Value)
{
	TIM15_16_17_PWM_CH1_SetValue(TIM16, PWM_Value);
}

// No more.
