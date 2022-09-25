/*
 * mpu9250.c
 *
 *  Created on: 22 sep. 2022
 *      Author: Santiago
 */


#include "port.h"
#include "types.h"


#define MPU9250_SLAVEADDR 0x0


retType APP_MPU9250Write(uint8_t addr, uint8_t * pdata, unit16_t size){

	retType ret = API_OK;

	if(size <= 0) ret = API_ERROR;
	if(ret != API_OK) return ret;

	ret |= DEV_WriteI2C(MPU9250_SLAVEADDR, pdata, size);

	return ret;
}

retType APP_MPU9250Read(uint8_t addr, uint8_t * pdata, unit16_t size){

	retType ret = API_OK;

	if(size <= 0) ret = API_ERROR;
	if(ret != API_OK) return ret;

	ret |= DEV_ReadI2C(MPU9250_SLAVEADDR, pdata, size);

	return ret;

}

retType APP_MPU9250Init(void){

	retType ret = API_OK;
	uint8_t *data;
}

retType APP_MPU9250ReadGyro(){

	retType ret = API_OK;
	return ret;
}

retType APP_MPU9250ReadAccl(){

	retType ret = API_OK;
	return ret;
}

retType APP_MPU9250ReadTemp(){

	retType ret = API_OK;
	return ret;
}
