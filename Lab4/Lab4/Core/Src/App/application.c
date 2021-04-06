/*
 * application.c
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */
/// INCLUDES ///
#include "SDK/interface.h"
#include "App/semaphore.h"
#include "App/commands.h"
#include "cmsis_os.h"

///  API  ///
void SDK_MAIN_PreLoop()
{
	SDK_TIM_AddInterrupt(&SDK_SYS_Shutdown, 7500, false);
	osKernelStart();

}
void SDK_MAIN_LoopFunc()
{
	//SEM_Cycle();
}
void SDK_MAIN_PostLoop()
{
	// turn off all colors
	//SDK_LED_Set(SDK_LED_GREEN, SDK_LED_OFF);
	//SDK_LED_Set(SDK_LED_YELLOW, SDK_LED_OFF);
	//SDK_LED_Set(SDK_LED_RED, SDK_LED_OFF);
}

void SDK_MAIN_ProcessCommand(const char* command)
{
	CMD_ProcessCommand(command);
}

void SDK_INT_AppCallback()
{
	//SDK_MAIN_Wrapper();
	//SDK_BTN_SetDown();
	//SDK_SYS_Shutdown();
}
