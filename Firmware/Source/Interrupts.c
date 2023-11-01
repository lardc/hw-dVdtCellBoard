﻿// Include
#include "stdinc.h"
#include "Controller.h"
#include "LowLevel.h"
#include "Board.h"
#include "Global.h"
#include "SysConfig.h"

// Functions
//
void EXTI0_IRQHandler()
{
	if(!GPIO_GetState(GPIO_SYNC_IN) && CONTROL_SubState == SDS_WaitSync)
	{
		LL_ExternalLED(true);
		TIM_Start(TIM7);

		CONTROL_SetDeviceState(DS_Powered, SDS_RiseEdgeDetected);
	}
	else
	{
		if(GPIO_GetState(GPIO_SYNC_IN) && CONTROL_SubState == SDS_RiseEdgeDetected)
			AfterPulseTimeout = CONTROL_TimeCounter + AFTER_PULSE_TIMEOUT;
	}

	EXTI_FlagReset(EXTI_0);
}
//-----------------------------------------

void USART1_IRQHandler()
{
	if(ZwSCI_RecieveCheck(USART1))
	{
		ZwSCI_RegisterToFIFO(USART1);
		ZwSCI_RecieveFlagClear(USART1);
	}
}
//-----------------------------------------

void TIM3_IRQHandler()
{
	static uint16_t CounterTmp = 0, CounterLed = 0;

	if(TIM_StatusCheck(TIM3))
	{
		if(++CounterTmp >= (1000 / TIMER3_uS))
		{
			CounterTmp = 0;
			CONTROL_TimeCounter++;
			
			if(++CounterLed >= LED_BLINK_TIME)
			{
				LL_ToggleLed();
				CounterLed = 0;
			}
		}
		
		ADC_SamplingStart(ADC1);
		CONTROL_Cycle();
		CONTROL_AfterPulseProcess();
		TIM_StatusClear(TIM3);
	}
}
//-----------------------------------------

void TIM7_IRQHandler()
{
	if(TIM_StatusCheck(TIM7))
		LL_CurrentLimitEnable(true);
	
	TIM_Stop(TIM7);
	TIM_StatusClear(TIM7);
}
//-----------------------------------------
