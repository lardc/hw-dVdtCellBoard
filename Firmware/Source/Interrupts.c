// Include
#include "Interrupts.h"
//
#include <InitConfig.h>
#include "stm32f30x.h"
#include "stdinc.h"
#include "DataTable.h"
#include "Controller.h"
#include "DeviceProfile.h"
#include "LowLevel.h"
#include "Board.h"
#include "SysConfig.h"

// Variables
//
volatile Int64U LED_BlinkTimeCounter = 0;

// Functions
//
void EXTI0_IRQHandler()
{
	EXTI_FlagReset(EXTI_0);
}
//-----------------------------------------

void USART1_IRQHandler()
{
	if (ZwSCI_RecieveCheck(USART1))
	{
		ZwSCI_RegisterToFIFO(USART1);
		ZwSCI_RecieveFlagClear(USART1);
	}
}
//-----------------------------------------

void TIM3_IRQHandler()
{
	if (TIM_StatusCheck(TIM3))
	{
		CONTROL_TimeCounterTemp++;

		if(CONTROL_TimeCounterTemp>=(1/TIMER3_uS*1000))
		{
			CONTROL_TimeCounterTemp = 0;

			CONTROL_TimeCounter++;

			if (CONTROL_TimeCounter > (LED_BlinkTimeCounter + LED_BLINK_TIME))
			{
				//Моргаем светодиодом
				if (!LL_IsBlinkLED())
					LL_BlinkLED(TRUE);
				else
					LL_BlinkLED(FALSE);

				LED_BlinkTimeCounter = CONTROL_TimeCounter;
			}
		}

		CONTROL_Cycle();
		TIM_StatusClear(TIM3);
	}
}
//-----------------------------------------
