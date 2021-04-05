#include "semaphore.h"
#include "sdk_interface.h"

static uint16_t s_currentColor;

void SEM_Blink(uint16_t color, uint32_t count, uint32_t delay)
{
	// turn off previous color
	SDK_LED_Set(s_currentColor, SDK_LED_OFF);

	// turn off-on some times
	for(int i = 0; i < count; i++)
	{
		SDK_LED_Set(color, SDK_LED_OFF);
		SDK_SYS_Delay(delay);
		SDK_LED_Set(color, SDK_LED_ON);
		SDK_SYS_Delay(delay);
	}

	s_currentColor = color;
}

void SEM_Show(uint16_t color)
{
	// turn off previous color
	SDK_LED_Set(s_currentColor, SDK_LED_OFF);

	// turn on color
	SDK_LED_Set(color, SDK_LED_ON);

	s_currentColor = color;
}

void SEM_InterruptDelay(uint32_t minDelay, uint32_t maxDelay)
{
	uint32_t passed = SDK_BTN_WaitDown(minDelay);
	if(passed)
	{
		SDK_SYS_Delay(minDelay - passed);
	}
	else
	{
		SDK_BTN_WaitDown(maxDelay - minDelay);
	}
}

void SEM_AutoMode()
{
	SEM_Show(SDK_LED_GREEN);
	SDK_SYS_Delay(SEM_GREEN_PERIOD);
	SEM_Blink(SDK_LED_GREEN, SEM_BLINK_COUNT, SEM_BLINK_PERIOD);

	SEM_Show(SDK_LED_YELLOW);
	SDK_SYS_Delay(SEM_YELLOW_PERIOD);

	SEM_Show(SDK_LED_RED);
	SEM_InterruptDelay(SEM_RED_PERIOD / 4, SEM_RED_PERIOD);
}

void SDK_MAIN_preLoop()
{
	s_currentColor = SDK_LED_RED;
}
void SDK_MAIN_loopFunc()
{
	SEM_AutoMode();
}
void SDK_MAIN_postLoop()
{
	// turn off all colors
	SDK_LED_Set(SDK_LED_GREEN, SDK_LED_OFF);
	SDK_LED_Set(SDK_LED_YELLOW, SDK_LED_OFF);
	SDK_LED_Set(SDK_LED_RED, SDK_LED_OFF);
}



