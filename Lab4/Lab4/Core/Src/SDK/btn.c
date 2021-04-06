/*
 * sdk_interface.h
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */

/// INCLUDES ///
#include "SDK/interface.h"

/// TYPES ///
typedef struct BtnState
{
	bool m_pressed;
	bool m_down;
	bool m_up;
} BtnState;

/// STATIC ///
static BtnState s_btnState;

///  API  ///
void SDK_BTN_ClearState()
{
	s_btnState.m_pressed = false;
	s_btnState.m_up = false;
	s_btnState.m_down = false;
}
void SDK_BTN_Update()
{
	bool btn = HAL_GPIO_ReadPin(SDK_BTN_GPIO, SDK_BTN_PIN) == GPIO_PIN_RESET;
	s_btnState.m_up = s_btnState.m_pressed && !btn;
	s_btnState.m_down = !s_btnState.m_pressed && btn;
	s_btnState.m_pressed = btn;

#if SDK_REMOTE_MODE
	if(s_btnState.m_down || s_btnState.m_up)
	{
		SDK_TRACE_Timestamp(SDK_BTN, btn);
	}
#endif
}
bool SDK_BTN_IsPressed()
{
	return s_btnState.m_pressed;
}
bool SDK_BTN_IsUp()
{
	return s_btnState.m_up;
}
bool SDK_BTN_IsDown()
{
	return s_btnState.m_down;
}
void SDK_BTN_SetDown()
{
	s_btnState.m_pressed = true;
	s_btnState.m_up = false;
	s_btnState.m_down = true;

#if SDK_REMOTE_MODE
	SDK_TRACE_Timestamp(SDK_BTN, true);
#endif
}
