/*
 * app_sm.c
 *
 *  Created on: 26 sep. 2022
 *      Author: Santiago
 */

#include "app_sm.h"
#include "types.h"
#include "mpu9250.h"

State_t states;
MPU9250_t read_buff;

retType APP_SMInit(void){

	retType ret = API_OK;

	states = SM_INIT;
	return ret;
}

retType APP_SMProccess(void){

	retType ret = API_OK;

	switch(states){
	case SM_INIT:
		ret |= DEV_UARTInit();
		if(ret != API_OK) return ret;
		ret |= DEV_InitI2C();
		if(ret != API_OK) return ret;
		ret |= APP_MPU9250Init();
		if(ret == API_OK) states = SM_READY2READ;
		break;
	case SM_READY2READ:
		ret |= APP_MPU9250ReadGyro(&read_buff->gyro);
		ret |= APP_MPU9250ReadAccl(&read_buff->accl);
		ret |= APP_MPU9250ReadTemp(&read_buff->temp);
		if(ret == API_OK) states = SM_CONVERT;
		break;
	case SM_CONVERT:
		//Convert values
		if(ret == API_OK) states = SM_PRINT;
		else states = SM_READY2READ;
		break;
	case SM_PRINT:
		//print by UART
		if(ret == API_OK) states = SM_READY2READ;
		else states = SM_READY2READ;
		break;
	default:
		ret = API_ERROR;
		break;
	}
	return ret;

}
