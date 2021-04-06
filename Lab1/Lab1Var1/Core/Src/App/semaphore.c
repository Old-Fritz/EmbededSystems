/*
 * application.c
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */

/// INCLUDES ///
#include <SDK/interface.h>
#include "App/semaphore.h"

static uint16_t s_currentColor;

/// API ///
void SEM_Init()
{
	s_currentColor = SDK_LED_RED;
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
	SEM_Show(SDK_LED_RED, SEM_RED_PERIOD, true);
}

void SEM_Show(uint16_t color, uint32_t delay, bool interruptible)
{
	// turn off previous color
	SDK_LED_Set(s_currentColor, SDK_LED_OFF);

	// update current state
	s_currentColor = color;

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
	SDK_LED_Set(s_currentColor, SDK_LED_OFF);

	// update current state
	s_currentColor = color;

	// turn off-on some times
	for(int i = 0; i < count; i++)
	{
		SDK_LED_Set(color, SDK_LED_OFF);
		SDK_TIM_Delay(delay);
		SDK_LED_Set(color, SDK_LED_ON);
		SDK_TIM_Delay(delay);
	}
}

