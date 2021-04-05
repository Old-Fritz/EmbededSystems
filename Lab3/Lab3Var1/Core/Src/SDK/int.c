/*
 * int.c
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */


/// INCLUDES ///
#include "SDK/interface.h"
#include "tim.h"

/// STATICS ///
__IO uint32_t s_ticksHP = 0;

///  API  ///
void SDK_INT_Init()
{
	// timer for app defined interruptions
	__HAL_TIM_CLEAR_FLAG(&SDK_INT_HANDLE_APP, TIM_SR_UIF);
	HAL_TIM_Base_Start_IT(&SDK_INT_HANDLE_APP);

	// timer for high frequency priority interruptions
	__HAL_TIM_CLEAR_FLAG(&SDK_INT_HANDLE_PRIORITY, TIM_SR_UIF);
	HAL_TIM_Base_Start_IT(&SDK_INT_HANDLE_PRIORITY);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == SDK_INT_TYPE_APP)
	{
#if SDK_REMOTE_MODE
		SDK_TRACE_Timestamp(SDK_INT, true);
#endif
		SDK_INT_AppCallback();
#if SDK_REMOTE_MODE
		SDK_TRACE_Timestamp(SDK_INT, false);
#endif
	}
	else if (htim->Instance == SDK_INT_TYPE_PROIORITY)
	{
		SDK_INT_PriorityCallback();
	}
}

void SDK_INT_PriorityCallback()
{
	s_ticksHP += 1;
}

uint32_t SDK_INT_GetTicks()
{
	return s_ticksHP;
}

void SDK_INT_Delay(uint32_t delay)
{
	uint32_t tickstart = SDK_INT_GetTicks();
	uint32_t wait = delay * SDK_INT_FREQ_MS_PRIORITY;

	// guarantee minimum wait
	wait += 1;

	while((SDK_INT_GetTicks() - tickstart) < wait)
	{
	}

}
