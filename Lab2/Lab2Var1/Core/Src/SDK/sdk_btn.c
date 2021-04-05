#include "SDK/sdk_interface.h"

typedef struct BtnState
{
	bool m_pressed;
	bool m_down;
	bool m_up;
} BtnState;

static BtnState s_btnState;

void SDK_BTN_ClearState()
{
	s_btnState.m_pressed = false;
	s_btnState.m_up = false;
	s_btnState.m_down = false;
}
void SDK_BTN_Update()
{
	// TODO: prevent mush
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
	bool status = s_btnState.m_pressed;

	return status;
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
uint32_t SDK_BTN_WaitDown(uint32_t timeout)
{
	uint32_t tickstart = HAL_GetTick();
	uint32_t wait = timeout + 1;
	uint32_t passed = 1;

	while( passed < wait)
	{
		if(SDK_BTN_IsDown() )
		{
			return passed;
		}
		passed = HAL_GetTick() - tickstart;
	}

	return 0;
}
