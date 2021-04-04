#include "trace.h"

/*
 * sdk_interface.h
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */

#ifndef INC_SDK_INTERFACE_H_
#define INC_SDK_INTERFACE_H_


#define SDK_LED_GPIO GPIOD
#define SDK_LED_ON GPIO_PIN_SET
#define SDK_LED_OFF GPIO_PIN_RESET

#define SDK_LED1 LED1
#define SDK_LED2 LED2
#define SDK_LED3 LED3
#define SDK_LED_GREEN LED1
#define SDK_LED_YELLOW LED2
#define SDK_LED_RED LED3

#define SDK_PIN_GREEN GPIO_PIN_13
#define SDK_PIN_YELLOW GPIO_PIN_14
#define SDK_PIN_RED GPIO_PIN_15

#define SDK_PIN_UNDEFINED 0


void SDK_Init();
void SDK_Shutdown();

void SDK_Delay(uint32_t delay);

void SDK_SetLed(uint16_t led, GPIO_PinState state);
void SDK_ToggleLed(uint16_t led);

void SDK_Print(char * format, ...);
void SDK_Dump(uint32_t addr, uint16_t size);

#endif /* INC_SDK_INTERFACE_H_ */
