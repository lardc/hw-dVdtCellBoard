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

	// Настройка системной частоты тактирования
	INITCFG_ConfigSystemClock();

	// Настройка портов
	INITCFG_ConfigIO();

	// Настройка ЦАП
	INITCFG_ConfigDAC();

	// Настройка внешних прерываний
	INITCFG_ConfigEI();

	// Настройка UART
	INITCFG_ConfigUART();

	// Настройка таймеров
	INITCFG_ConfigTimer3();

	//Настройка ШИМ
	INITCFG_ConfigPWM();

	// Настройка АЦП
	INITCFG_ConfigADC();

	// Настройка сторожевого таймера
	INITCFG_ConfigWatchDog();

	// Инициализация логики контроллера
	CONTROL_Init();

	// Фоновый цикл
	while (TRUE)
		CONTROL_Idle();

	return 0;
}
