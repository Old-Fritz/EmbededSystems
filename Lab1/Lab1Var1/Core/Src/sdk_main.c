/*
 * sdk_main.c
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */


#include "sdk_interface.h"


void SDK_MAIN_wrapper()
{
	SDK_SYS_Init();

	SDK_MAIN_preLoop();
	SDK_MAIN_loop();
	SDK_MAIN_postLoop();

	SDK_SYS_Shutdown();
}

void SDK_MAIN_loop()
{
#if !SDK_REMOTE_MODE
	while(true)
#else
	for(int i = 0; i < SDK_MAIN_LOOP_REPEATS; i++)
#endif
	{
		SDK_MAIN_loopFunc();
	}
}
