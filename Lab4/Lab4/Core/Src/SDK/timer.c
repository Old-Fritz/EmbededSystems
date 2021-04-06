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

/// STATIC ///
static Interrupt s_interrupt[SDK_TIM_INTERRUPT_MAX];
static uint32_t s_interruptCount = 0;

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
}
