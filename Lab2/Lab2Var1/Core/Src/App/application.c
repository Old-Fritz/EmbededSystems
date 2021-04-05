/*
 * application.c
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */

#include "App/semaphore.h"
#include "App/commands.h"

void SDK_MAIN_PreLoop()
{
	// init semaphore
	SEM_Init();

#if SDK_REMOTE_MODE
	// simulate button press
	SDK_TIM_SetInterrupt(&SDK_BTN_SetDown, SEM_BTN_PERIOD);
#endif
}
void SDK_MAIN_LoopFunc()
{
	SEM_Cycle();
}
void SDK_MAIN_PostLoop()
{
	// turn off all colors
	SDK_LED_Set(SDK_LED_GREEN, SDK_LED_OFF);
	SDK_LED_Set(SDK_LED_YELLOW, SDK_LED_OFF);
	SDK_LED_Set(SDK_LED_RED, SDK_LED_OFF);
}

void SDK_MAIN_ProcessCommand(const char* command)
{
	CMD_ProcessCommand(command);
}
