/*
 * API_UART.h
 *
 *  Created on: 24 sep. 2022
 *      Author: Santiago
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

/* Includes ------------------------------------------------------------------*/
#include "types.h"

/* Exported typedefine ------------------------------------------------------------*/

//Define UART functions
retType DEV_UARTInit(void);
retType DEV_UARTSendString(uint8_t * pstring);
retType DEV_UARTSendStringSize(uint8_t * pstring, uint16_t size);
retType DEV_UARTReceiveStringSize(uint8_t * pstring, uint16_t size);




#endif /* API_INC_API_UART_H_ */
