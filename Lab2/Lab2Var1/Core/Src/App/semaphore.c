#include "App/semaphore.h"
#include "SDK/sdk_interface.h"

static SemaphoreState s_semaphoreState;

void SEM_Init()
{
	s_semaphoreState.m_color = ECS_Red;
	s_semaphoreState.m_mode = ESM_ProcessPress;
	s_semaphoreState.m_redTimeout = SEM_RED_PERIOD;
}

static uint16_t MapColorStateToLed(eColorState color)
{
	switch(color)
	{
	case ECS_Green:
		return SDK_LED_GREEN;
	case ECS_Yellow:
		return SDK_LED_YELLOW;
	case ECS_Red:
		return SDK_LED_RED;
	case ECS_BlinkingGreen:
		return SDK_LED_GREEN;
	}
	return 0;
}
static eColorState MapLedToColorState(uint16_t led, bool isBlinking)
{
	switch(led)
	{
	case SDK_LED_GREEN:
		return isBlinking ? ECS_BlinkingGreen : ECS_Green;
	case SDK_LED_YELLOW:
		return ECS_Yellow;
	case SDK_LED_RED:
		return ECS_Red;
	}
	return 0;
}
void SEM_Blink(uint16_t color, uint32_t count, uint32_t delay)
{
	// turn off previous color
	SDK_LED_Set(MapColorStateToLed(s_semaphoreState.m_color), SDK_LED_OFF);

	// turn off-on some times
	for(int i = 0; i < count; i++)
	{
		SDK_LED_Set(color, SDK_LED_OFF);
		SDK_SYS_Delay(delay);
		SDK_LED_Set(color, SDK_LED_ON);
		SDK_SYS_Delay(delay);
	}

	s_semaphoreState.m_color = MapLedToColorState(color, true);
}

void SEM_Show(uint16_t color)
{
	// turn off previous color
	SDK_LED_Set(MapColorStateToLed(s_semaphoreState.m_color), SDK_LED_OFF);

	// turn on color
	SDK_LED_Set(color, SDK_LED_ON);

	s_semaphoreState.m_color = MapLedToColorState(color, false);
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
	if(s_semaphoreState.m_mode == ESM_IgnorePress)
	{
		SDK_SYS_Delay(s_semaphoreState.m_redTimeout);
	}
	else
	{
		SEM_InterruptDelay(s_semaphoreState.m_redTimeout / 4, s_semaphoreState.m_redTimeout);
	}
}

SemaphoreState SEM_GetState()
{
	return s_semaphoreState;
}
void SEM_SetMode(eSemaphoreMode mode)
{
	s_semaphoreState.m_mode = mode;
}
void SEM_SetRedTimeout(uint32_t timeout)
{
	s_semaphoreState.m_redTimeout = timeout;
}

void SDK_MAIN_PreLoop()
{
	SDK_TIM_SetInterrupt(&SDK_BTN_SetDown, SEM_BTN_PERIOD);
	SEM_Init();
}
void SDK_MAIN_LoopFunc()
{
	SEM_AutoMode();
}
void SDK_MAIN_PostLoop()
{
	// turn off all colors
	SDK_LED_Set(SDK_LED_GREEN, SDK_LED_OFF);
	SDK_LED_Set(SDK_LED_YELLOW, SDK_LED_OFF);
	SDK_LED_Set(SDK_LED_RED, SDK_LED_OFF);
}



