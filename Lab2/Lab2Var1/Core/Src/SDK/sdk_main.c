/*
 * sdk_main.c
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */


#include "SDK/sdk_interface.h"


void SDK_MAIN_Wrapper()
{
	SDK_SYS_Init();

	SDK_MAIN_PreLoop();
	SDK_MAIN_Loop();
	SDK_MAIN_PostLoop();

	SDK_SYS_Shutdown();
}

void SDK_MAIN_Loop()
{
#if !SDK_REMOTE_MODE
	while(true)
#else
	for(int i = 0; i < SDK_MAIN_LOOP_REPEATS; i++)
#endif
	{
		SDK_MAIN_LoopFunc();
	}
}
