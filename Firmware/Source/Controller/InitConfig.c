#include <InitConfig.h>
#include "SysConfig.h"

// Forward functions
//
void CONTROL_Init();


// Functions
//
Boolean SysClk_Config()
{
	return RCC_PLL_HSE_Config(QUARTZ_FREQUENCY, PREDIV_4, PLL_14);
}
//------------------------------------------------------------------------------

void EI_Config()
{
	// Sync
	EXTI_Config(EXTI_PB, EXTI_0, FALL_TRIG, 0);
	EXTI_EnableInterrupt(EXTI0_IRQn, 0, true);
}
//------------------------------------------------------------------------------

void IO_Config()
{
	// Включение тактирования портов
	RCC_GPIO_Clk_EN(PORTA);
	RCC_GPIO_Clk_EN(PORTB);

	// Аналоговые порты
	GPIO_Config (GPIOA, Pin_0, Analog, NoPull, HighSpeed, NoPull);				// PA0 - вход АЦП (напряжение батареи)
	GPIO_Config(GPIOA, Pin_4, Analog, NoPull, HighSpeed, NoPull);				// PA4 - выход ЦАП

	// Цифровые входы
	GPIO_Config(GPIOB, Pin_0, Input, NoPull, HighSpeed, NoPull);				// PB0 - START_PULSE - вход синхронизации

	// Выходы
	GPIO_Config (GPIOA, Pin_5,  Output, PushPull, HighSpeed, NoPull);			// PA5 - I_LIM - смена ограничения по току в выходном каскаде
	GPIO_Bit_Rst(GPIOA, Pin_5);
	GPIO_Config (GPIOA, Pin_6,  Output, PushPull, HighSpeed, NoPull);			// PA6 - BRAKE_PWM - цепь разряда
	GPIO_Bit_Rst(GPIOA, Pin_6);
	GPIO_Config (GPIOA, Pin_15,  Output, PushPull, HighSpeed, NoPull);			// PA15 - LED1
	GPIO_Bit_Rst(GPIOA, Pin_15);
	GPIO_Config (GPIOB, Pin_4,  Output, PushPull, HighSpeed, NoPull);			// PB4 - LED2
	GPIO_Bit_Rst(GPIOB, Pin_4);

	// Альтернативные функции
	GPIO_Config (GPIOB, Pin_6, AltFn, PushPull, HighSpeed, NoPull);				// PB6(USART1 TX)
	GPIO_AltFn  (GPIOB, Pin_6, AltFn_7);
	GPIO_Config (GPIOB, Pin_7, AltFn, PushPull, HighSpeed, NoPull);				// PB7(USART1 RX)
	GPIO_AltFn  (GPIOB, Pin_7, AltFn_7);
	GPIO_Config (GPIOA, Pin_2, AltFn, PushPull, HighSpeed, NoPull);				// PA2(TIM15_CH1 - PWM)
	GPIO_AltFn  (GPIOA, Pin_2, AltFn_9);
}
//------------------------------------------------------------------------------

void CAN_Config()
{
	RCC_CAN_Clk_EN(CAN_1_ClkEN);
	NCAN_Init(SYSCLK, CAN_BAUDRATE, FALSE);
	NCAN_FIFOInterrupt(TRUE);
	NCAN_FilterInit(0, 0, 0);		// Фильтр 0 пропускает все сообщения
}
//------------------------------------------------------------------------------

void UART_Config()
{
	USART_Init(USART1, SYSCLK, USART_BAUDRATE);
	USART_Recieve_Interupt(USART1, 0, true);
}
//------------------------------------------------------------------------------

void ADC_Init()
{
	RCC_ADC_Clk_EN(ADC_12_ClkEN);
	ADC_Calibration(ADC1);
	ADC_SoftTrigConfig(ADC1);
	ADC_ChannelSet_SampleTime(ADC1, 1, ADC_SMPL_TIME_7_5);
	ADC_Enable(ADC1);
}
//------------------------------------------------------------------------------

void Timer3_Config()
{
	TIM_Clock_En(TIM_3);
	TIM_Config(TIM3, SYSCLK, TIMER3_uS);
	TIM_Interupt(TIM3, 0, true);
	TIM_Start(TIM3);
}
//------------------------------------------------------------------------------

void Timer6_Config()
{
	TIM_Clock_En(TIM_6);
	TIM_Config(TIM6, SYSCLK, TIMER3_uS);
	TIM_Interupt(TIM6, 0, true);
	TIM_Start(TIM6);
}
//------------------------------------------------------------------------------

void WatchDog_Config()
{
	IWDG_Config();
	IWDG_ConfigureFastUpdate();
}
//------------------------------------------------------------------------------

void PWM_Config()
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

void InitializeController(Boolean GoodClock)
{
	CONTROL_Init();
}
// -----------------------------------------------------------------------------

void DAC_Config()
{
	DACx_Clk_Enable(DAC_1_ClkEN);
	DACx_Reset();
	DAC_Trigger_Config(TRIG1_TIMER6, TRIG1_ENABLE);
	DAC_Buff(BUFF1, false);
	DACx_Enable(DAC1ENABLE);
}
// -----------------------------------------------------------------------------
