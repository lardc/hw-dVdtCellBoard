#include "Interrupts.h"
#include "InitConfig.h"
#include "SysConfig.h"
#include "Controller.h"

// Functions
//
void CONTROL_Idle();

int main()
{
	//__disable_irq();
	//SCB->VTOR = (uint32_t)BOOT_LOADER_MAIN_PR_ADDR;
	__enable_irq();

	// ��������� ��������� ������� ������������
	INITCFG_ConfigSystemClock();

	// ��������� ������
	INITCFG_ConfigIO();

	// ��������� ���
	INITCFG_ConfigDAC();

	// ��������� ������� ����������
	INITCFG_ConfigEI();

	// ��������� UART
	INITCFG_ConfigUART();

	// ��������� ��������
	INITCFG_ConfigTimer3();

	//��������� ���
	INITCFG_ConfigPWM();

	// ��������� ���
	INITCFG_ConfigADC();

	// ��������� ����������� �������
	INITCFG_ConfigWatchDog();

	// ������������� ������ �����������
	CONTROL_Init();

	// ������� ����
	while (TRUE)
		CONTROL_Idle();

	return 0;
}
