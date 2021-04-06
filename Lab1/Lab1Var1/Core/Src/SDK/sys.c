/*
 * sdk_interface.c
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */

/// INCLUDES ///
#include "SDK/interface.h"

///  API  ///
// system API
void SDK_SYS_Init()
{
#if SDK_REMOTE_MODE
	MX_TRACE_Init();
	SDK_TRACE_Start();
#endif
	SDK_BTN_ClearState();
}
void SDK_SYS_Shutdown()
{
#if SDK_REMOTE_MODE
	SDK_TRACE_Stop();
#endif
}
void SDK_SYS_Tick()
{
	SDK_BTN_Update();
	SDK_TIM_Update();
}

// led API
static uint16_t LED_MapLedToPin(uint16_t led)
{
	switch(led)
	{
	case SDK_LED_GREEN:
		return SDK_LED_GREEN_PIN;
	case SDK_LED_YELLOW:
		return SDK_LED_YELLOW_PIN;
	case SDK_LED_RED:
		return SDK_LED_RED_PIN;
	default:
		return 0;
	};
}
void SDK_LED_Set(uint16_t led, GPIO_PinState state)
{
	uint16_t pin = LED_MapLedToPin(led);

	HAL_GPIO_WritePin(SDK_LED_GPIO, pin, state);
#if SDK_REMOTE_MODE
	SDK_TRACE_Timestamp(led, HAL_GPIO_ReadPin(SDK_LED_GPIO, pin));
#endif
}
void SDK_LED_Toggle(uint16_t led)
{
	uint16_t pin = LED_MapLedToPin(led);

	HAL_GPIO_TogglePin(SDK_LED_GPIO, pin);
#if SDK_REMOTE_MODE
	SDK_TRACE_Timestamp(led, HAL_GPIO_ReadPin(SDK_LED_GPIO, pin));
#endif
}

// debug API
void SDK_DBG_Print(char * format, ...)
{
#if SDK_REMOTE_MODE
	va_list args;
	va_start(args, format);

	SDK_TRACE_Timestamp(PRINT, 1);
	SDK_TRACE_VPrint(format, args);
	SDK_TRACE_Timestamp(PRINT, 0);
#endif
}
void SDK_DBG_Dump(uint32_t addr, uint16_t size)
{
#if SDK_REMOTE_MODE
	SDK_TRACE_Timestamp(DUMP, 1);
	SDK_TRACE_Dump(addr, size);
	SDK_TRACE_Timestamp(DUMP, 0);
#endif
}
