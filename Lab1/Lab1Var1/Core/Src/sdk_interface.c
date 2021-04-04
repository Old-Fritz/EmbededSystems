/*
 * sdk_interface.c
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */

#include "sdk_interface.h"
#include <stdarg.h>

void SDK_Init()
{
	MX_TRACE_Init();
	SDK_TRACE_Start();
}
void SDK_Shutdown()
{
	SDK_TRACE_Stop();
}

void SDK_Delay(uint32_t delay)
{
	HAL_Delay(delay);
}


static uint16_t MapLedToPin(uint16_t led)
{
	switch(led)
	{
	case SDK_LED_GREEN:
		return SDK_PIN_GREEN;
	case SDK_LED_YELLOW:
		return SDK_PIN_YELLOW;
	case SDK_LED_RED:
		return SDK_PIN_RED;
	default:
		return SDK_PIN_UNDEFINED;
	};
}
void SDK_SetLed(uint16_t led, GPIO_PinState state)
{
	uint16_t pin = MapLedToPin(led);

	HAL_GPIO_WritePin(SDK_LED_GPIO, pin, state);
	SDK_TRACE_Timestamp(led, HAL_GPIO_ReadPin(SDK_LED_GPIO, pin));
}
void SDK_ToggleLed(uint16_t led)
{
	uint16_t pin = MapLedToPin(led);

	HAL_GPIO_TogglePin(SDK_LED_GPIO, pin);
	SDK_TRACE_Timestamp(led, HAL_GPIO_ReadPin(SDK_LED_GPIO, pin));
}

void SDK_Print(char * format, ...)
{
	va_list args;
	va_start(args, format);

	SDK_TRACE_Timestamp(PRINT, 1);
	SDK_TRACE_Print(format, args);
	SDK_TRACE_Timestamp(PRINT, 0);

	va_end (args);
}
void SDK_Dump(uint32_t addr, uint16_t size)
{
	SDK_TRACE_Timestamp(DUMP, 1);
	SDK_TRACE_Dump(addr, size);
	SDK_TRACE_Timestamp(DUMP, 0);
}
