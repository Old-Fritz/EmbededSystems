/*
 * application.c
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */

/// INCLUDES ///
#include <SDK/interface.h>
#include "App/semaphore.h"

/// STATIC ///
static SemaphoreState s_semaphoreState;

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

/// API ///
void SEM_Init()
{
	s_semaphoreState.m_color = ECS_Red;
	s_semaphoreState.m_mode = ESM_ProcessPress;
	s_semaphoreState.m_redTimeout = SEM_RED_PERIOD;
}

void SEM_Cycle()
{
	// green
	SEM_Show(SDK_LED_GREEN, SEM_GREEN_PERIOD, false);
	// blinking green
	SEM_Blink(SDK_LED_GREEN, SEM_BLINK_PERIOD, SEM_BLINK_COUNT);

	// yellow
	SEM_Show(SDK_LED_YELLOW, SEM_YELLOW_PERIOD, false);

	// red
	SEM_Show(SDK_LED_RED, s_semaphoreState.m_redTimeout, s_semaphoreState.m_mode == ESM_ProcessPress);
}

void SEM_Show(uint16_t color, uint32_t delay, bool interruptible)
{
	// turn off previous color
	SDK_LED_Set(MapColorStateToLed(s_semaphoreState.m_color), SDK_LED_OFF);

	// update current state
	s_semaphoreState.m_color = MapLedToColorState(color, false);

	// turn on color
	SDK_LED_Set(color, SDK_LED_ON);

	// perform delay
	if(interruptible)
	{
		SDK_TIM_InterruptDelay(delay / 4, delay);
	}
	else
	{
		SDK_TIM_Delay(delay);
	}
}

void SEM_Blink(uint16_t color, uint32_t delay, uint32_t count)
{
	// turn off previous color
	SDK_LED_Set(MapColorStateToLed(s_semaphoreState.m_color), SDK_LED_OFF);

	// update current state
	s_semaphoreState.m_color = MapLedToColorState(color, true);

	// turn off-on some times
	for(int i = 0; i < count; i++)
	{
		SDK_LED_Set(color, SDK_LED_OFF);
		SDK_TIM_Delay(delay);
		SDK_LED_Set(color, SDK_LED_ON);
		SDK_TIM_Delay(delay);
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



