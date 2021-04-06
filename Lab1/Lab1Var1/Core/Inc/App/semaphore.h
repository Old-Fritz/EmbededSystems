/*
 * semaphore.h
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */
#ifndef INC_SEMAPHORE_H_
#define INC_SEMAPHORE_H_

/// INCLUDES ///
#include "SDK/interface.h"

/// CONFIG ///
#define SEM_BLINK_COUNT 2
#define SEM_BLINK_PERIOD 50
#define SEM_GREEN_PERIOD 200
#define SEM_YELLOW_PERIOD 50
#define SEM_RED_PERIOD 650
#define SEM_BTN_PERIOD 510

///  API  ///
void SEM_Init();
void SEM_Cycle();

void SEM_Show(uint16_t color, uint32_t delay, bool interruptible);
void SEM_Blink(uint16_t color, uint32_t delay, uint32_t count);

#endif /* INC_SEMAPHORE_H_ */
