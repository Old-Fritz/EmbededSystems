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

///  API  ///
void SDK_MAIN_PreLoop()
{
	// Init semaphore
	SEM_Init();

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

int counter = 0;
void SDK_INT_AppCallback()
{
	GPIO_PinState stateGreen = SDK_LED_Read(SDK_LED_GREEN);
	GPIO_PinState stateYellow = SDK_LED_Read(SDK_LED_YELLOW);
	GPIO_PinState stateRed = SDK_LED_Read(SDK_LED_RED);

	SDK_LED_Set(SDK_LED_GREEN, SDK_LED_ON);
	SDK_LED_Set(SDK_LED_YELLOW, SDK_LED_OFF);
	SDK_LED_Set(SDK_LED_RED, SDK_LED_ON);

	SDK_INT_Delay(2000);

	SDK_LED_Set(SDK_LED_GREEN, stateGreen);
	SDK_LED_Set(SDK_LED_YELLOW, stateYellow);
	SDK_LED_Set(SDK_LED_RED, stateRed);
}
