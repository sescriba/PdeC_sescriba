/*
 * mpu9250.h
 *
 *  Created on: 22 sep. 2022
 *      Author: Santiago
 */

#ifndef DEV_INC_MPU9250_H_
#define DEV_INC_MPU9250_H_

#include "types.h"

typedef struct{
	uint16_t x;
	uint16_t y;
	uint16_t z;
}axis_t;

typedef struct{
	axis_t gyro;
	axis_t accl;
	uint16_t temp;
}MPU9250_t;

retType APP_MPU9250Write(uint8_t addr2write, uint8_t * pdata, uint16_t size);
retType APP_MPU9250Read(uint8_t addr2read, uint8_t * pdata, uint16_t size);
retType APP_MPU9250Init(void);
retType APP_MPU9250ReadGyro(axis_t * gyro);
retType APP_MPU9250ReadAccl(axis_t * accl);
retType APP_MPU9250ReadTemp(uint16_t * temp);


#endif /* DEV_INC_MPU9250_H_ */
