#ifndef __BOARD_H
#define __BOARD_H

#include "Delay.h"
#include "stm32f30x.h"

#include "ZwRCC.h"
#include "ZwGPIO.h"
#include "ZwNCAN.h"
#include "ZwTIM.h"
#include "ZwDAC.h"
#include "ZwDMA.h"
#include "ZwADC.h"
#include "ZwEXTI.h"
#include "ZwSCI.h"
#include "ZwIWDG.h"
#include "ZwNFLASH.h"

//����������� ��� ���������� ������
GPIO_PortPinSettingMacro GPIO_MEASURE_V 	= {GPIOA, Pin_0};	// ���������� �� ������ �������������� ��
GPIO_PortPinSettingMacro GPIO_DAC_V 		= {GPIOA, Pin_4};	// ��� - �������

// ����������� ��� �������/�������� ������
GPIO_PortPinSettingMacro GPIO_SYNC_IN	  	= {GPIOB, Pin_0};
GPIO_PortPinSettingMacro GPIO_I_LIM			= {GPIOA, Pin_5};
GPIO_PortPinSettingMacro GPIO_LED1	 	 	= {GPIOA, Pin_15};
GPIO_PortPinSettingMacro GPIO_LED2	 	 	= {GPIOB, Pin_4};
GPIO_PortPinSettingMacro GPIO_LOW_VRATE		= {GPIOB, Pin_12};
GPIO_PortPinSettingMacro GPIO_MID_VRATE	 	= {GPIOB, Pin_15};
GPIO_PortPinSettingMacro GPIO_HIGH_VRATE	= {GPIOA, Pin_10};

// ����������� ��� ������ �������������� �������
GPIO_PortPinSettingMacro GPIO_ALT_UART_RX 	= {GPIOB, Pin_7};
GPIO_PortPinSettingMacro GPIO_ALT_UART_TX	= {GPIOB, Pin_6};
GPIO_PortPinSettingMacro GPIO_ALT_PWM_FB  	= {GPIOA, Pin_2};
GPIO_PortPinSettingMacro GPIO_ALT_PWM_BRAKE	= {GPIOA, Pin_6};

#endif // __BOARD_H
