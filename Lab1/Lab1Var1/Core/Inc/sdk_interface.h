#include "trace.h"
#include <stdbool.h>

/*
 * sdk_interface.h
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */

#ifndef INC_SDK_INTERFACE_H_
#define INC_SDK_INTERFACE_H_

// define 0 if local launch
#define SDK_REMOTE_MODE 1

#define SDK_MAIN_LOOP_REPEATS 2

// Button input
#define SDK_BTN_GPIO GPIOC
#define SDK_BTN P0
#define SDK_BTN_PIN GPIO_PIN_15

// LED output
#define SDK_LED_GPIO GPIOD
#define SDK_LED_ON GPIO_PIN_SET
#define SDK_LED_OFF GPIO_PIN_RESET

#define SDK_LED1 LED1
#define SDK_LED2 LED2
#define SDK_LED3 LED3
#define SDK_LED_GREEN LED1
#define SDK_LED_YELLOW LED2
#define SDK_LED_RED LED3

#define SDK_LED_GREEN_PIN GPIO_PIN_13
#define SDK_LED_YELLOW_PIN GPIO_PIN_14
#define SDK_LED_RED_PIN GPIO_PIN_15

// main cycle wrapper
void SDK_MAIN_wrapper();
void SDK_MAIN_loop();

void SDK_MAIN_preLoop();
void SDK_MAIN_postLoop();
void SDK_MAIN_loopFunc();

// system API
void SDK_SYS_Init();
void SDK_SYS_Shutdown();

void SDK_SYS_Delay(uint32_t delay);

// button API
void SDK_BTN_ClearState();
void SDK_BTN_Update();
void SDK_BTN_SetDown();

bool SDK_BTN_IsPressed();
bool SDK_BTN_IsUp();
bool SDK_BTN_IsDown();

uint32_t SDK_BTN_WaitDown(uint32_t timeout);

// led API
void SDK_LED_Set(uint16_t led, GPIO_PinState state);
void SDK_LED_Toggle(uint16_t led);

// debug API
void SDK_DBG_Print(char * format, ...);
void SDK_DBG_Dump(uint32_t addr, uint16_t size);

#endif /* INC_SDK_INTERFACE_H_ */
