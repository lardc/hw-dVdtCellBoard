#ifndef __SYSCONFIG_H
#define __SYSCONFIG_H


// Flash loader options
#define BOOT_LOADER_VARIABLE			(*((volatile uint32_t *)0x20000000))
#define BOOT_LOADER_REQUEST				0x12345678
#define BOOT_LOADER_MAIN_PR_ADDR		0x00000000
//-----------------------------------------------

// System clock
#define SYSCLK							70000000	// �������� ������� ��������� ���� ����������
#define QUARTZ_FREQUENCY				20000000	// ������� ������
// ----------------------------------------------

// USART
//#define USART_BAUDRATE				115200		// �������� USART
#define USART_BAUDRATE					78125		// �������� USART
#define USART_FIFOlen					32			// ����� FIFO USART
// ----------------------------------------------

// Timers
#define TIMER3_uS						200			// ������ ������ ������� 3
#define TIMER6_uS						10			// ������ ������ ������� 6
#define TIMER15_uS						10			// ������ ������ ������� 15
#define TIMER16_uS						10			// ������ ������ ������� 16
// ----------------------------------------------

// CAN
#define CAN_BAUDRATE					1000000		// ������� CAN
// ----------------------------------------------

// ADC Channels
#define ADC_CH_V_CAP					1
// ----------------------------------------------


#endif // __SYSCONFIG_H
