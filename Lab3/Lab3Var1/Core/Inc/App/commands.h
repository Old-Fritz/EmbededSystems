/*
 * commands.h
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */

#ifndef INC_COMMANDS_H_
#define INC_COMMANDS_H_

/// INCLUDES ///
#include "SDK/interface.h"

/// TYPES ///
typedef enum eCmdType
{
	ECT_GetInfo,			// '?'
	ECT_SetMode,			// 'set mode X'
	ECT_SetTimeout,			// 'set timeout X'
	ECT_SetInterrupts,		// 'set interrupts X'
	ECT_Undefined
} eCmdType;

typedef struct CmdData
{
	eCmdType m_type;
	uint32_t m_arg;
} CmdData;

/// API ///
void CMD_ProcessCommand(const char* command);
void CMD_GetInfo();

CmdData CMD_ParseComand(const char* command);

bool CMD_ParseGetInfo(const char* command, int strSize, CmdData* data);
bool CMD_ParseSet(const char* command, int strSize, CmdData* data);
bool CMD_ParseSetMode(const char* command, int strSize, CmdData* data);
bool CMD_ParseSetTimeout(const char* command, int strSize, CmdData* data);
bool CMD_ParseSetInterrupts(const char* command, int strSize, CmdData* data);

#endif /* INC_COMMANDS_H_ */
