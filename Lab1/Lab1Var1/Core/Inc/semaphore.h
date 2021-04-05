/*
 * semaphore.h
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */
#include "stdint.h"

#ifndef INC_SEMAPHORE_H_
#define INC_SEMAPHORE_H_

#define SEM_BLINK_COUNT 3
#define SEM_BLINK_PERIOD 50
#define SEM_GREEN_PERIOD 250
#define SEM_YELLOW_PERIOD 100
#define SEM_RED_PERIOD 500

void SEM_Blink(uint16_t color, uint32_t count, uint32_t delay);
void SEM_Interrupt(uint32_t minDelay, uint32_t maxDelay);
void SEM_Show(uint16_t color);
void SEM_AutoMode();

#endif /* INC_SEMAPHORE_H_ */
