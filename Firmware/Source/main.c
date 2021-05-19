#include "Interrupts.h"
#include "InitConfig.h"
#include "SysConfig.h"
#include "Controller.h"

// Functions
//
void CONTROL_Idle();

int main()
{
	__enable_irq();

	// ��������� ��������� ������� ������������
	INITCFG_ConfigSystemClock();

	// ��������� ������� ����������
	INITCFG_ConfigEI();

	// ��������� ������
	INITCFG_ConfigIO();

	// ��������� UART
	INITCFG_ConfigUART();

	// ��������� ���
	INITCFG_ConfigADC();

	// ��������� DMA
	INITCFG_ConfigDMA();

	// ��������� ��������
	INITCFG_ConfigTimer3();
	INITCFG_ConfigTimer6();
	INITCFG_ConfigTimer7();

	// ��������� ����������� �������
	INITCFG_ConfigWatchDog();

	// ��������� �������� ���
	INITCFG_ConfigPWM();

	// ��������� ���
	INITCFG_ConfigDAC();

	// ������������� ������ �����������
	CONTROL_Init();

	// ������� ����
	while (TRUE)
		CONTROL_Idle();

	return 0;
}
