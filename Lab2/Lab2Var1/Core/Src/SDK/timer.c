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
	uint32_t m_delay;
	uint32_t m_timer;
	bool m_periodic;
} Interrupt;
typedef struct DataInterrupt
{
	void (*m_callbackPtr)(void* data);
	void* m_data;
	uint32_t m_delay;
	uint32_t m_timer;
	bool m_periodic;
} DataInterrupt;

/// STATIC ///
static Interrupt s_interrupt[SDK_TIM_INTERRUPT_MAX];
static uint32_t s_interruptCount = 0;

static DataInterrupt s_dataInterrupt[SDK_TIM_DATA_INTERRUPT_MAX];
static uint32_t s_dataInterruptCount = 0;
/// API ///

void SDK_TIM_AddInterrupt(void(*callbackPtr)(), uint32_t delay, bool periodic)
{
	if(s_interruptCount < SDK_TIM_INTERRUPT_MAX)
	{
		s_interrupt[s_interruptCount].m_callbackPtr = callbackPtr;
		s_interrupt[s_interruptCount].m_delay = delay;
		s_interrupt[s_interruptCount].m_timer = 0;
		s_interrupt[s_interruptCount].m_periodic = periodic;

		s_interruptCount++;
	}
}
void SDK_TIM_AddDataInterrupt(void(*callbackPtr)(void* data), void* data, uint32_t delay, bool periodic)
{
	if(s_dataInterruptCount < SDK_TIM_DATA_INTERRUPT_MAX)
	{
		s_dataInterrupt[s_dataInterruptCount].m_callbackPtr = callbackPtr;
		s_dataInterrupt[s_dataInterruptCount].m_data = data;
		s_dataInterrupt[s_dataInterruptCount].m_delay = delay;
		s_dataInterrupt[s_dataInterruptCount].m_timer = 0;
		s_dataInterrupt[s_dataInterruptCount].m_periodic = periodic;

		s_dataInterruptCount++;
	}
}

void SDK_TIM_Update()
{
	for(int i = 0; i < s_interruptCount; ++i)
	{
		if(s_interrupt[i].m_callbackPtr && ++s_interrupt[i].m_timer >= s_interrupt[i].m_delay)
		{
			s_interrupt[i].m_timer = 0;
			s_interrupt[i].m_callbackPtr();
			if(!s_interrupt[i].m_periodic)
			{
				s_interrupt[i].m_callbackPtr = 0;
			}
		}
	}

	for(int i = 0; i < s_dataInterruptCount; ++i)
	{
		if(s_dataInterrupt[i].m_callbackPtr && ++s_dataInterrupt[i].m_timer >= s_dataInterrupt[i].m_delay)
		{
			s_dataInterrupt[i].m_timer = 0;
			s_dataInterrupt[i].m_callbackPtr(s_dataInterrupt[i].m_data);
			if(!s_dataInterrupt[i].m_periodic)
			{
				s_dataInterrupt[i].m_callbackPtr = 0;
			}
		}
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
