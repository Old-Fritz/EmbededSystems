/*
 * sdk_timer.c
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */

/// INCLUDES ///
#include "SDK/interface.h"

/// TYPES ///
typedef struct Interrupt
{
	void (*m_callbackPtr)();
	uint32_t m_period;
	uint32_t m_timer;

} Interrupt;

/// STATIC ///
static Interrupt s_interrupt;

/// API ///
void SDK_TIM_SetInterrupt(void(*callbackPtr)(), uint32_t period)
{
	s_interrupt.m_callbackPtr = callbackPtr;
	s_interrupt.m_period = period;
	s_interrupt.m_timer = 0;
}

void SDK_TIM_Update()
{
	if(++s_interrupt.m_timer >= s_interrupt.m_period)
	{
		s_interrupt.m_timer = 0;
		s_interrupt.m_callbackPtr();
	}
}

void SDK_TIM_Delay(uint32_t delay)
{
	HAL_Delay(delay);
}

void SDK_TIM_InterruptDelay(uint32_t minDelay, uint32_t maxDelay)
{
	uint32_t passed = SDK_TIM_WaitEvent(SDK_BTN_IsDown, minDelay);
	if(passed)
	{
		SDK_TIM_Delay(minDelay - passed);
	}
	else
	{
		SDK_TIM_WaitEvent(SDK_BTN_IsDown, maxDelay - minDelay);
	}
}

uint32_t SDK_TIM_WaitEvent(bool (*event)(), uint32_t timeout)
{
	uint32_t tickstart = HAL_GetTick();

	// +1 to be sure that return positive if event() is true
	uint32_t wait = timeout + 1;
	uint32_t passed = 1;

	while( passed < wait)
	{
		if(event())
		{
			return passed;
		}
		passed = HAL_GetTick() - tickstart;
	}

	return 0;
}
