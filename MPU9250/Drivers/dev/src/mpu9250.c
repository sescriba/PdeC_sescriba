/*
 * mpu9250.c
 *
 *  Created on: 22 sep. 2022
 *      Author: Santiago
 */


#include "mpu9250.h"
#include "port.h"

#define MPU9250_SLAVEADDR 0x68
#define MPU9250_PWR_MGMT_1 0x6B
#define MPU9250_CONFIG_AD 0x1A
#define MPU9250_GYRO_CONFIG 0x1B
#define MPU9250_ACCEL_CONFIG_1 0x1C
#define MPU9250_ACCEL_CONFIG_2 0x1D


retType APP_MPU9250Write(uint8_t * addr2write, uint8_t * pdata, uint16_t size){

	retType ret = API_OK;

	if(size <= 0) ret = API_ERROR;
	if(ret != API_OK) return ret;

	ret |= DEV_WriteI2C(MPU9250_SLAVEADDR, addr2write, 1);
	ret |= DEV_WriteI2C(MPU9250_SLAVEADDR, pdata, size);

	return ret;
}

retType APP_MPU9250Read(uint8_t * addr2read, uint8_t * pdata, uint16_t size){

	retType ret = API_OK;

	if(size <= 0) ret = API_ERROR;
	if(ret != API_OK) return ret;

	ret |= DEV_WriteI2C(MPU9250_SLAVEADDR, addr2read, 1);
	ret |= DEV_ReadI2C(MPU9250_SLAVEADDR, pdata, size);

	return ret;

}

retType APP_MPU9250Init(void){

	retType ret = API_OK;
//	uint8_t *data;

	ret |= APP_MPU9250Write(MPU9250_PWR_MGMT_1, 0x1, 1);
	if(ret != API_OK) return ret;
	ret |= APP_MPU9250Write(MPU9250_GYRO_CONFIG, 0x8, 1);
	ret |= APP_MPU9250Write(MPU9250_ACCEL_CONFIG_1, 0x8, 1);
	ret |= APP_MPU9250Write(MPU9250_ACCEL_CONFIG_2, 0x5, 1);
	if(ret != API_OK) return ret;
	ret |= APP_MPU9250Write(MPU9250_CONFIG_AD, 0x5, 1);
	return ret;

}

retType APP_MPU9250ReadGyro(axis_t * gyro){

	retType ret = API_OK;

	return ret;
}

retType APP_MPU9250ReadAccl(axis_t * accl){

	retType ret = API_OK;
	return ret;
}

retType APP_MPU9250ReadTemp(uint8_t * temp){

	retType ret = API_OK;
	return ret;
}
