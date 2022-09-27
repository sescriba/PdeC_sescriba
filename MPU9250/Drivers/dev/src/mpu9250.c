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
#define MPU9250_ACCEL_XOUT_H 0x3B
#define MPU9250_ACCEL_XOUT_L 0x3C
#define MPU9250_ACCEL_YOUT_H 0x3D
#define MPU9250_ACCEL_YOUT_L 0x3E
#define MPU9250_ACCEL_ZOUT_H 0x3F
#define MPU9250_ACCEL_ZOUT_L 0x40
#define MPU9250_TEMP_OUT_H 0x41
#define MPU9250_TEMP_OUT_L 0x42
#define MPU9250_GYRO_XOUT_H 0x43
#define MPU9250_GYRO_XOUT_L 0x44
#define MPU9250_GYRO_YOUT_H 0x45
#define MPU9250_GYRO_YOUT_L 0x46
#define MPU9250_GYRO_ZOUT_H 0x47
#define MPU9250_GYRO_ZOUT_L 0x48

static uint8_t gyro_convert(uint8_t axis);
static uint8_t accl_convert(uint8_t axis);
static uint8_t temp_convert(uint8_t temp);

retType APP_MPU9250Write(uint8_t addr2write, uint8_t * pdata, uint16_t size){

	retType ret = API_OK;

	if(size <= 0) ret = API_ERROR;
	if(ret != API_OK) return ret;

	ret |= DEV_I2CWrite(MPU9250_SLAVEADDR, &addr2write, 1);
	ret |= DEV_I2CWrite(MPU9250_SLAVEADDR, pdata, size);

	return ret;
}

retType APP_MPU9250Read(uint8_t addr2read, uint8_t * pdata, uint16_t size){

	retType ret = API_OK;

	if(size <= 0) ret = API_ERROR;
	if(ret != API_OK) return ret;

	ret |= DEV_I2CWrite(MPU9250_SLAVEADDR, &addr2read, 1);
	ret |= DEV_I2CRead(MPU9250_SLAVEADDR, pdata, size);

	return ret;

}

retType APP_MPU9250Init(void){

	retType ret = API_OK;
//	uint8_t *data;

	ret |= APP_MPU9250Write(MPU9250_PWR_MGMT_1, (uint8_t*)0x1, 1);
	if(ret != API_OK) return ret;
	ret |= APP_MPU9250Write(MPU9250_GYRO_CONFIG, (uint8_t*)0x8, 1);
	ret |= APP_MPU9250Write(MPU9250_ACCEL_CONFIG_1, (uint8_t*)0x8, 1);
	ret |= APP_MPU9250Write(MPU9250_ACCEL_CONFIG_2, (uint8_t*)0x5, 1);
	if(ret != API_OK) return ret;
	ret |= APP_MPU9250Write(MPU9250_CONFIG_AD, (uint8_t*)0x5, 1);
	return ret;

}

retType APP_MPU9250ReadGyro(axis_t * gyro){

	retType ret = API_OK;
	uint8_t aux_x = 0;
	uint8_t aux_y = 0;
	uint8_t aux_z = 0;

	ret |= APP_MPU9250Read(MPU9250_GYRO_XOUT_H, &aux_x, 2);
	ret |= APP_MPU9250Read(MPU9250_GYRO_YOUT_H, &aux_y, 2);
	ret |= APP_MPU9250Read(MPU9250_GYRO_ZOUT_H, &aux_z, 2);

	*gyro->x = gyro_convert(aux_x);
	*gyro->y = gyro_convert(aux_y);
	*gyro->z = gyro_convert(aux_z);
	return ret;
}

retType APP_MPU9250ReadAccl(axis_t * accl){

	retType ret = API_OK;
	uint8_t aux_x = 0;
	uint8_t aux_y = 0;
	uint8_t aux_z = 0;

	ret |= APP_MPU9250Read(MPU9250_ACCEL_XOUT_H, &aux_x, 2);
	ret |= APP_MPU9250Read(MPU9250_ACCEL_YOUT_H, &aux_y, 2);
	ret |= APP_MPU9250Read(MPU9250_ACCEL_ZOUT_H, &aux_z, 2);

	*accl->x = accl_convert(aux_x);
	*accl->y = accl_convert(aux_y);
	*accl->z = accl_convert(aux_z);
	return ret;
}

retType APP_MPU9250ReadTemp(uint8_t * temp){

	retType ret = API_OK;
	uint8_t aux_temp = 0;

	ret |= APP_MPU9250Read(MPU9250_TEMP_OUT_H, &aux_temp, 2);

	*temp = temp_convert(aux_temp);
	return ret;
}

static uint8_t gyro_convert(uint8_t axis){

	uint8_t value = 0;

	value = axis;
	return value;
}

static uint8_t accl_convert(uint8_t axis){

	uint8_t value = 0;

	value = axis;
	return value;
}

static uint8_t temp_convert(uint8_t temp){

	uint8_t value = 0;

	value = temp;
	return value;
}
