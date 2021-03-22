#include "InitConfig.h"
#include "Board.h"
#include "SysConfig.h"
#include "Controller.h"
#include "LowLevel.h"
#include "Global.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "BCCIxParams.h"

// Functions
//
Boolean INITCFG_ConfigSystemClock()
{
	return RCC_PLL_HSE_Config(QUARTZ_FREQUENCY, PREDIV_4, PLL_14);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigEI()
{
	// Sync
	EXTI_Config(EXTI_PB, EXTI_0, FALL_TRIG, 0);
	EXTI_EnableInterrupt(EXTI0_IRQn, 0, true);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigIO()
{
	// Включение тактирования портов
	RCC_GPIO_Clk_EN(PORTA);
	RCC_GPIO_Clk_EN(PORTB);

	// Аналоговые порты
	GPIO_InitAnalog(GPIO_MEASURE_V);
	GPIO_InitAnalog(GPIO_DAC_V);

	// Цифровые входы
	GPIO_InitInput(GPIO_SYNC_IN, NoPull);

	// Выходы
	GPIO_InitPushPullOutput(GPIO_I_LIM);
	GPIO_SetState(GPIO_I_LIM, false);
	GPIO_InitPushPullOutput (GPIO_BRAKE_PWM);
	GPIO_SetState(GPIO_BRAKE_PWM, false);
	GPIO_InitPushPullOutput (GPIO_LED1);
	GPIO_SetState(GPIO_LED1, false);
	GPIO_InitPushPullOutput (GPIO_LED2);
	GPIO_SetState(GPIO_LED2, false);

	// Альтернативные функции
	GPIO_InitAltFunction(GPIO_ALT_UART_RX, AltFn_7);
	GPIO_InitAltFunction(GPIO_ALT_UART_TX, AltFn_7);
	GPIO_InitAltFunction(GPIO_ALT_PWM, AltFn_9);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigUART()
{
	USART_Init(USART1, SYSCLK, USART_BAUDRATE);
	USART_Recieve_Interupt(USART1, 0, true);
}
//------------------------------------------------

void INITCFG_ConfigADC()
{
	RCC_ADC_Clk_EN(ADC_12_ClkEN);

	ADC_Calibration(ADC1);
	ADC_SoftTrigConfig(ADC1);
	ADC_Enable(ADC1);

	//ADC_Calibration(ADC1);
	//ADC_TrigConfig(ADC1, ADC12_TIM6_TRGO, RISE);
	//ADC_ChannelSeqReset(ADC1);
	//ADC_ChannelSet_Sequence(ADC1, ADC_CH_V_CAP, 1);
	//ADC_ChannelSeqLen(ADC1, 1);
	//ADC_Enable(ADC1);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigTimer3()
{
	TIM_Clock_En(TIM_3);
	TIM_Config(TIM3, SYSCLK, TIMER3_uS);
	TIM_Interupt(TIM3, 1, true);
	TIM_Start(TIM3);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigTimer6()
{
	TIM_Clock_En(TIM_6);
	TIM_Config(TIM6, SYSCLK, TIMER6_uS);
	TIM_DMA(TIM6, DMAEN);
	TIM_MasterMode(TIM6, MMS_UPDATE);
}
//------------------------------------------------

void INITCFG_ConfigWatchDog()
{
	IWDG_Config();
	IWDG_ConfigureFastUpdate();
}
//------------------------------------------------------------------------------

void INITCFG_ConfigPWM()
{
	//PA2 - Flyback PWM
	TIM_Clock_En(TIM_15);
	TIM15_16_17_PWM_CH1_Config(TIM15, SYSCLK, TIMER15_uS);
	TIM_Start(TIM15);

	//PA6 - Brake PWM
	TIM_Clock_En(TIM_16);
	TIM15_16_17_PWM_CH1_Config(TIM16, SYSCLK, TIMER16_uS);
	TIM_Start(TIM16);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigDAC()
{
	DACx_Clk_Enable(DAC_1_ClkEN);
	DACx_Reset();
	//DAC_TriggerConfigCh1(DAC1, TRIG1_TIMER6, TRIG1_ENABLE);
	DAC_TriggerConfigCh1(DAC1, TRIG1_SOFTWARE, TRIG1_ENABLE);
	DAC_BufferCh1(DAC1, false);
	DAC_EnableCh1(DAC1);
}
// -----------------------------------------------------------------------------
