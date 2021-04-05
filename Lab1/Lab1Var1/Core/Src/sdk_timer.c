/*
 * sdk_timer.c
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */


#include "sdk_interface.h"

typedef struct Interrupt
{
	void (*m_callbackPtr)();
	uint32_t m_period;
	uint32_t m_timer;

} Interrupt;

Interrupt s_interrupt;


void SDK_TIM_SetInterrupt(void(*callbackPtr)(), uint32_t period)
{
	s_interrupt.m_callbackPtr = callbackPtr;
	s_interrupt.m_period = period;
	s_interrupt.m_timer = 0;
}

void SDK_TIM_Inc()
{
	if(++s_interrupt.m_timer >= s_interrupt.m_period)
	{
		s_interrupt.m_timer = 0;
		s_interrupt.m_callbackPtr();
	}
}
