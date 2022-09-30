/*
 * app_sm.h
 *
 *  Created on: 26 sep. 2022
 *      Author: Santiago
 */

#ifndef INC_APP_SM_H_
#define INC_APP_SM_H_

#include "types.h"

typedef enum{
	SM_INIT,
	SM_READGYRO,
	SM_READACCL,
	SM_READTEMP,
	SM_PRINT,
	SM_IDLE,
	SM_ERROR,
} State_t;

retType APP_SMInit(void);
retType APP_SMProccess(void);

#endif /* INC_APP_SM_H_ */
