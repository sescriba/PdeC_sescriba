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
#include "string.h"

State_t states;
State_t prv_state;
MPU9250_t read_buff;
bool_t it_i2c;
bool_t first_time;

static retType print_string(MPU9250_t * data);

retType APP_SMInit(void){

	retType ret = API_OK;

	states = SM_INIT;
	return ret;
}

retType APP_SMProccess(void){

	retType ret = API_OK;
	uint8_t * str;

	switch(states){
		case SM_INIT:
			ret |= DEV_UARTInit();
			if(ret != API_OK){
				states = SM_ERROR;
				break;
			}
			ret |= DEV_I2CInit();
			if(ret != API_OK){
				states = SM_ERROR;
				break;
			}
			ret |= APP_MPU9250Init();
			if(ret == API_OK){
				states = SM_READGYRO;
				it_i2c = false;
				first_time = true;
			}
			else{
				states = SM_ERROR;
				break;
			}
			break;
		case SM_READGYRO:
			if(first_time){
				ret |= APP_MPU9250ReadGyro(&read_buff.gyro);
				if(ret != API_OK){
					states = SM_ERROR;
					break;
				}
				first_time = false;
			}
			if(it_i2c == true){
				states = SM_READACCL;
				it_i2c = false;
				first_time = true;
			}
			else{
				prv_state = states;
				states = SM_IDLE;
			}
			break;
		case SM_READACCL:
			if(first_time){
				ret |= APP_MPU9250ReadAccl(&read_buff.accl);
				if(ret != API_OK){
					states = SM_ERROR;
					break;
				}
				first_time = false;
			}
			if(it_i2c == true){
				states = SM_READTEMP;
				it_i2c = false;
				first_time = true;
			}
			else{
				prv_state = states;
				states = SM_IDLE;
			}
			break;
		case SM_READTEMP:
			if(first_time){
				ret |= APP_MPU9250ReadTemp(&read_buff.temp);
				if(ret != API_OK){
					states = SM_ERROR;
					break;
				}
				first_time = false;
			}
			if(it_i2c == true){
				states = SM_PRINT;
				it_i2c = false;
				first_time = true;
			}
			else{
				prv_state = states;
				states = SM_IDLE;
			}
			break;
		case SM_PRINT:
			ret |= print_string(&read_buff);
			if(ret == API_OK) states = SM_READGYRO;
			break;
		case SM_IDLE:
			it_i2c = true;	//debug
			if(it_i2c == true){
				states = prv_state;
				it_i2c = false;
			}
			break;
		case SM_ERROR:
		default:
			ret = API_ERROR;
			break;
	}
	return ret;
}

static retType print_string(MPU9250_t * data){

	retType ret = API_OK;
	uint8_t buff[128] = {0};
	uint8_t value[5] = {0};
	uint8_t str[] = "Data returned: ";
	uint8_t str_gyro[] = "\nGyroscope:";
	uint8_t str_accl[] = "\nAccelerometer:";
	uint8_t str_temp[] = "\nTemperature:";
	uint8_t str_x[] = "\nAxis X: ";
	uint8_t str_y[] = "\nAxis Y: ";
	uint8_t str_z[] = "\nAxis Z: ";
	uint8_t i = 0;

	strcat(buff, str);
	strcat(buff, str_gyro);
	strcat(buff, str_x);
	itoa(data->gyro.x, value, 10);
	strcat(buff, value);
	strcat(buff, str_y);
	itoa(data->gyro.y, value, 10);
	strcat(buff, value);
	strcat(buff, str_z);
	itoa(data->gyro.z, value, 10);
	strcat(buff, value);

	strcat(buff, str_accl);
	strcat(buff, str_x);
	itoa(data->accl.x, value, 10);
	strcat(buff, value);
	strcat(buff, str_y);
	itoa(data->accl.y, value, 10);
	strcat(buff, value);
	strcat(buff, str_z);
	itoa(data->accl.z, value, 10);
	strcat(buff, value);

	strcat(buff, str_temp);
	itoa(data->temp, value, 10);
	strcat(buff, value);
	strcat(buff, "C");

	for(i = 0; i<128; i++){
		if(buff[i] == '\0') return ret;
		DEV_UARTSendChar(&buff[i]);
	}
	return ret;
}
