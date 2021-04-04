#include "semaphore.h"
#include "sdk_interface.h"

void SEM_Blink(uint16_t color)
{
	// turn off all colors
	SDK_SetLed(SDK_LED_GREEN, SDK_LED_OFF);
	SDK_SetLed(SDK_LED_YELLOW, SDK_LED_OFF);
	SDK_SetLed(SDK_LED_RED, SDK_LED_OFF);

	for(int i = 0; i < SEM_BLINK_COUNT; i++)
	{
		SDK_SetLed(color, SDK_LED_ON);
		SDK_Delay(SEM_BLINK_PERIOD);
		SDK_SetLed(color, SDK_LED_OFF);
		SDK_Delay(SEM_BLINK_PERIOD);
	}
}

void SEM_Show(uint16_t color)
{
	// turn off all colors
	SDK_SetLed(SDK_LED_GREEN, SDK_LED_OFF);
	SDK_SetLed(SDK_LED_YELLOW, SDK_LED_OFF);
	SDK_SetLed(SDK_LED_RED, SDK_LED_OFF);

	// turn on color
	SDK_SetLed(color, SDK_LED_ON);
}

void SEM_AutoMode()
{
	SEM_Show(SDK_LED_GREEN);
	SDK_Delay(SEM_GREEN_PERIOD);
	SEM_Blink(SDK_LED_GREEN);

	SEM_Show(SDK_LED_YELLOW);
	SDK_Delay(SEM_YELLOW_PERIOD);

	SEM_Show(SDK_LED_RED);
	SDK_Delay(SEM_RED_PERIOD);
}
