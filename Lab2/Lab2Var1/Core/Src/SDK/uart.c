/*
 * sdk_uart.c
 *
 *  Created on: 5 апр. 2021 г.
 *      Author: komar
 */

/// INCLUDES ///
#include "SDK/interface.h"
#include "usart.h"

/// TYPES ///
typedef struct UartData
{
	bool m_interrupts;
	uint8_t m_buffer[SDK_UART_BUFFER_SIZE];
} UartData;

/// STATIC ///
static UartData s_uartData;
static void SDK_UART_StartReceiving();
static void SDK_UART_ContinueReceiving();

static void SDK_UART_StartReceiving()
{
	if(s_uartData.m_interrupts)
	{
		// will be recieved by callback
		HAL_UART_Receive_IT(&SDK_UART_HANDLE, s_uartData.m_buffer, 1);
	}
	else
	{
		// wait for first byte
		while(HAL_UART_Receive(&SDK_UART_HANDLE, s_uartData.m_buffer, 1, SDK_UART_TIMEOUT) != HAL_OK) { }
		SDK_UART_ContinueReceiving();	}
}
static void SDK_UART_ContinueReceiving()
{
	SDK_UART_Receive(s_uartData.m_buffer, SDK_UART_BUFFER_SIZE, 1 );
	SDK_MAIN_ProcessCommand((const char*)s_uartData.m_buffer);
	SDK_UART_StartReceiving();
}

/// API ///
void SDK_UART_Init()
{
	s_uartData.m_interrupts = true;
	SDK_UART_StartReceiving();
}
void SDK_UART_EnableInterrupts(bool interrupts)
{
	s_uartData.m_interrupts = interrupts;
}

void SDK_UART_Transmit(uint8_t* pData, size_t size)
{
	HAL_UART_Transmit(&SDK_UART_HANDLE, pData, size, SDK_UART_TIMEOUT);

	SDK_DBG_Print("Uart: %s", pData);
}

void SDK_UART_Receive(uint8_t* pData, size_t size, size_t offset)
{
	uint32_t dataInd = offset;

	while(dataInd < size - 1 &&
			HAL_UART_Receive(&SDK_UART_HANDLE, pData + dataInd, 1, SDK_UART_TIMEOUT) == HAL_OK)
	{
		dataInd++;
	}
	pData[dataInd] = 0;
	SDK_UART_Transmit(pData, dataInd);
}


bool SDK_UART_IsInterruptible()
{
	return s_uartData.m_interrupts;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	SDK_UART_ContinueReceiving();
}
