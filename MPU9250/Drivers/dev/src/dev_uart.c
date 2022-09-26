/*
 * API_UART.c
 *
 *  Created on: 24 sep. 2022
 *      Author: Santiago
 */

#include "dev_uart.h"
#include "stm32f4xx_hal_uart.h"

//Define Macros
#define USARTx 					USART3
#define UART_BAUDRATE 			9600
#define UART_HWFLOWCTL 			UART_HWCONTROL_NONE
#define UART_MODE 				UART_MODE_TX_RX
#define UART_OVERSAMPLING 		UART_OVERSAMPLING_16
#define UART_PARITY 			UART_PARITY_ODD
#define UART_STOPBITS 			UART_STOPBITS_1
#define UART_WORDLENGTH 		UART_WORDLENGTH_8B
#define TIME_OUT 				0xFFFF

//UART Handle
UART_HandleTypeDef huart;

/**
  * @brief  Send String via UART
  * @param  uint8_t *
  * @retval Void
  */
retType DEV_UARTSendString(uint8_t * pstring){

	retType ret = API_OK;

	if(sizeof(pstring) == 0) return API_ERROR;
	ret |= HAL_UART_Transmit(&huart, pstring, sizeof(pstring), TIME_OUT);

	return ret;
}

/**
  * @brief  Send String and size via UART
  * @param  uint8_t *, uint16_t
  * @retval Void
  */
retType DEV_UARTSendStringSize(uint8_t * pstring, uint16_t size){

	retType ret = API_OK;

	if(size == 0) return API_ERROR;
	ret |= HAL_UART_Transmit(&huart, pstring, size, TIME_OUT);

	return ret;
}

/**
  * @brief  Receive String and size via UART
  * @param  uint8_t *, uint16_t
  * @retval Void
  */
retType DEV_UARTReceiveStringSize(uint8_t * pstring, uint16_t size){

	retType ret = API_OK;

	if(size == 0) return API_ERROR;
	ret |= HAL_UART_Receive(&huart, pstring, size, TIME_OUT);

	return ret;
}

/**
  * @brief  Configurate UART port
  * @param  Void
  * @retval bool_t
  */
retType DEV_UARTInit(void){

	retType ret = API_OK;

	uint8_t str[] = "UART INITIALIZED:\n";

	huart.Instance = USARTx;
	huart.Init.BaudRate= UART_BAUDRATE;
	huart.Init.HwFlowCtl = UART_HWFLOWCTL;
	huart.Init.Mode = UART_MODE;
	huart.Init.OverSampling = UART_OVERSAMPLING;
	huart.Init.Parity = UART_PARITY;
	huart.Init.StopBits = UART_STOPBITS;
	huart.Init.WordLength = UART_WORDLENGTH;

	ret |= HAL_UART_Init(&huart);
	if(ret != API_OK) return ret;
	else uartSendString(str);
	return ret;
}