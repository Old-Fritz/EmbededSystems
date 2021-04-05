/*
 * Commands.c
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */

/// INCLUDES ///
#include "App/commands.h"
#include "App/semaphore.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

/// STATIC ///
static char* MapColorStateToName(eColorState color)
{
	switch(color)
	{
	case ECS_Green:
		return "Green";
	case ECS_Yellow:
		return "Yellow";
	case ECS_Red:
		return "Red";
	case ECS_BlinkingGreen:
		return "Blinking Green";
	}
	return "";
}
static char* MapModeToName(eSemaphoreMode mode)
{
	switch(mode)
	{
	case ESM_ProcessPress:
		return "Process";
	case ESM_IgnorePress:
		return "Ignore";
	}
	return "";
}
static char* MapBool(bool value)
{
	if(value)
	{
		return "true";
	}
	return "false";
}

/// API ///
void CMD_ProcessCommand(const char* command)
{
	CmdData data = CMD_ParseComand(command);
	switch(data.m_type)
	{
	case ECT_GetInfo:
		CMD_GetInfo();
		break;
	case ECT_SetMode:
		SEM_SetMode(data.m_arg);
		break;
	case ECT_SetTimeout:
		SEM_SetRedTimeout(data.m_arg);
		break;
	case ECT_SetInterrupts:
		SDK_UART_EnableInterrupts(data.m_arg);
		break;
	default:
		break;
	}
}
void CMD_GetInfo()
{
	SemaphoreState info = SEM_GetState();
	char buffer[128];

	sprintf("Color: %s  ModeOnPress: %s  Red timeout: %d  Interrupts: %s",
			MapColorStateToName(info.m_color), MapModeToName(info.m_mode),
			info.m_redTimeout, MapBool(SDK_UART_IsInterruptible()));

	SDK_UART_Transmit((uint8_t*)buffer, strlen(buffer));
}

// parsing
CmdData CMD_ParseComand(const char* command)
{
	CmdData data;
	data.m_type = ECT_Undefined;
	data.m_arg = 0;

	size_t strSize = strlen(command);
	uint32_t commandStart = 0;

	// find first non-space symbol
	while (commandStart < strSize && isspace((int)command[commandStart]))
	{
		commandStart++;
	}
	if (commandStart == strSize)
	{
		return data;
	}
	command = command + commandStart;
	strSize -= commandStart;

	// try parse as different commands
	if (CMD_ParseGetInfo(command, strSize, &data))
	{
		return data;
	}
	if (CMD_ParseSet(command, strSize, &data))
	{
		return data;
	}

	return data;
}

bool CMD_ParseGetInfo(const char* command, int strSize, CmdData* data)
{
	char* pCh = strstr(command, "?");
	if (command && pCh == command &&
		(strSize == 1 || isspace((int)command[1])))
	{
		data->m_type = ECT_GetInfo;
		data->m_arg = 0;
		return true;
	}
	return false;
}

bool CMD_ParseSet(const char* command, int strSize, CmdData* data)
{
	char* pCh = strstr(command, "set");
	if (command && pCh == command &&
		strSize > 3 && isspace((int)command[3]))
	{
		uint32_t commandStart = 3;
		while (commandStart < strSize && isspace((int)command[commandStart]))
		{
			commandStart++;
		}
		if (commandStart == strSize)
		{
			return false;
		}
		command = command + commandStart;
		strSize -= commandStart;


		if (CMD_ParseSetMode(command, strSize, data))
		{
			return true;
		}
		if (CMD_ParseSetTimeout(command, strSize, data))
		{
			return true;
		}
		if (CMD_ParseSetInterrupts(command, strSize, data))
		{
			return true;
		}
	}
	return false;
}

bool CMD_ParseSetMode(const char* command, int strSize, CmdData* data)
{
	int value;
	uint32_t success = sscanf(command, "mode %d", &value);
	if (success == 1)
	{
		data->m_type = ECT_SetMode;
		data->m_arg = value;
		return true;
	}
	return false;
}
bool CMD_ParseSetTimeout(const char* command, int strSize, CmdData* data)
{
	int value;
	uint32_t success = sscanf(command, "timeout %d", &value);
	if (success == 1)
	{
		data->m_type = ECT_SetTimeout;
		data->m_arg = value;
		return true;
	}
	return false;
}
bool CMD_ParseSetInterrupts(const char* command, int strSize, CmdData* data)
{
	int value;
	uint32_t success = sscanf(command, "interrupts %d", &value);
	if (success == 1)
	{
		data->m_type = ECT_SetInterrupts;
		data->m_arg = value;
		return true;
	}
	return false;
}


