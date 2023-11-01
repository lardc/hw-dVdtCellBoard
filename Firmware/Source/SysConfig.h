﻿#ifndef __SYSCONFIG_H
#define __SYSCONFIG_H


// Flash loader options
#define BOOT_LOADER_VARIABLE			(*((volatile uint32_t *)0x20000000))
#define BOOT_LOADER_REQUEST				0x12345678
#define BOOT_LOADER_MAIN_PR_ADDR		0x00000000
//-----------------------------------------------

// System clock
#define SYSCLK							70000000	// Тактовая частота системной шины процессора
#define QUARTZ_FREQUENCY				20000000	// Частота кварца
// ----------------------------------------------

// USART
#define USART_BAUDRATE					78125		// Скорость USART
#define USART_FIFOlen					32			// Длина FIFO USART
// ----------------------------------------------

// Timers
#define TIMER3_uS						200			// Период работы таймера 3
#define TIMER6_uS						10			// Период работы таймера 6
#define TIMER7_uS						14			// Период работы таймера 6
#define TIMER15_uS						10			// Период работы таймера 15
#define TIMER16_uS						500			// Период работы таймера 16
// ----------------------------------------------

// ADC
#define DMA_ADC_V_BAT_CHANNEL			DMA1_Channel1	// Канал DMA для АЦП напряжения батареи
#define ADC1_V_BAT_CHANNEL				1				// АЦП1 номер канала напряжения
#define ADC_DMA_BUFF_SIZE				10				// Количество данных для DMA
// ----------------------------------------------



#endif // __SYSCONFIG_H
