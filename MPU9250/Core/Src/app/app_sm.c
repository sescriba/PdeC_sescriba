/*
 * app_sm.c
 *
 *  Created on: 26 sep. 2022
 *      Author: Santiago
 */

#include "app_sm.h"
#include "mpu9250.h"
#include "dev_uart.h"
#include "port.h"

State_t states;
MPU9250_t *read_buff;
bool_t it_i2c;
bool_t first_time;

retType APP_SMInit(void){

	retType ret = API_OK;

	states = SM_INIT;
	return ret;
}

retType APP_SMProccess(void){

	retType ret = API_OK;
	uint8_t str[] = "Data to print\n";

	switch(states){
		case SM_INIT:
			ret |= DEV_UARTInit();
			if(ret != API_OK) return ret;
			ret |= DEV_I2CInit();
			if(ret != API_OK) return ret;
			ret |= APP_MPU9250Init();
			if(ret == API_OK){
				states = SM_READGYRO;
				it_i2c = false;
				first_time = true;
			}
			break;
		case SM_READGYRO:
			if(first_time){
				ret |= APP_MPU9250ReadGyro(read_buff->gyro);
				first_time = false;
			}
			if(ret == API_OK && it_i2c == true){
				states = SM_READACCL;
				it_i2c = false;
				first_time = true;
			}
			break;
		case SM_READACCL:
			if(first_time){
				ret |= APP_MPU9250ReadAccl(read_buff->accl);
				first_time = false;
			}
			if(ret == API_OK && it_i2c == true){
				states = SM_READTEMP;
				it_i2c = false;
				first_time = true;
			}
		case SM_READTEMP:
			if(first_time){
				ret |= APP_MPU9250ReadTemp(read_buff->temp);
				first_time = false;
			}
			if(ret == API_OK && it_i2c == true){
				states = SM_PRINT;
				it_i2c = false;
				first_time = true;
			};
		case SM_PRINT:
			DEV_UARTSendStringSize(str, sizeof(str));
			if(ret == API_OK) states = SM_READGYRO;
			break;
		default:
			ret = API_ERROR;
			break;
	}
	return ret;

}