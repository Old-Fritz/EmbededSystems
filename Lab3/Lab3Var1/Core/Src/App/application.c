/*
 * application.c
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */
/// INCLUDES ///
#include "App/semaphore.h"
#include "App/commands.h"

///  API  ///
void SDK_MAIN_PreLoop()
{
	SDK_DBG_Print("%s", "Begin simulation");
	// init semaphore
	SEM_Init();

#if SDK_REMOTE_MODE
	// simulate button press
	SDK_TIM_AddInterrupt(&SDK_BTN_SetDown, SEM_BTN_PERIOD, true);

	// simulate command input
	SDK_TIM_AddDataInterrupt(&SDK_MAIN_ProcessCommand, "set interrupts 0", 100,  false);
	SDK_TIM_AddDataInterrupt(&SDK_MAIN_ProcessCommand, "set timeout 100", 100,  false);
	SDK_TIM_AddDataInterrupt(&SDK_MAIN_ProcessCommand, "set mode 2", 700,  false);
	SDK_TIM_AddDataInterrupt(&SDK_MAIN_ProcessCommand, "?", 1000, false);
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
