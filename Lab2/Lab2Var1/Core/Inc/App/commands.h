/*
 * commands.h
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */

#ifndef INC_COMMANDS_H_
#define INC_COMMANDS_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum eCmdType
{
	ECT_GetInfo,
	ECT_SetMode,
	ECT_SetTimeout,
	ECT_SetInterrupts,
	ECT_Undefined
} eCmdType;

typedef struct CmdData
{
	eCmdType m_type;
	uint32_t m_arg;
} CmdData;

void CMD_ProcessCommand(const char* command);
CmdData CMD_ParseComand(const char* command);

bool CMD_ParseGetInfo(const char* command, int strSize, CmdData* data);
bool CMD_ParseSet(const char* command, int strSize, CmdData* data);
bool CMD_ParseSetMode(const char* command, int strSize, CmdData* data);
bool CMD_ParseSetTimeout(const char* command, int strSize, CmdData* data);
bool CMD_ParseSetInterrupts(const char* command, int strSize, CmdData* data);

#endif /* INC_COMMANDS_H_ */
