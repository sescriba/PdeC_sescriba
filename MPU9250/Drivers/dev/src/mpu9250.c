/**
 ******************************************************************************
 * @file    Drivers/dev/src/mpu9250.c
 * @author  Santiago Escriba
 * @brief   File with High Level driver for MPU9250.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "mpu9250.h"

/* Private define ------------------------------------------------------------*/
#define MPU9250_SLAVEADDR 0xD0
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

/* Private function prototypes -----------------------------------------------*/
static retType gyro_convert(uint16_t axis, uint16_t * paxis);
static retType accl_convert(uint16_t axis, uint16_t * paxis);
static retType temp_convert(uint16_t temp, uint16_t * ptemp);

/* Exposed Function  ---------------------------------------------------------*/
/**
 * @brief  MPU9250 Write word
 * @param
 * 		addr2write	[I] - MPU Slave address
 * 		pdata 		[I] - Data Buffer
 * 		size 		[I] - Data Buffer size
 * @retval ret - Return API value
 */
retType APP_MPU9250Write(uint8_t addr2write, uint8_t * pdata, uint16_t size){

	retType ret = API_OK;

	if(size <= 0) ret = API_ERROR;
	if(ret != API_OK) return ret;

	ret |= DEV_I2CWrite(MPU9250_SLAVEADDR, &addr2write, 1);
	ret |= DEV_I2CWrite(MPU9250_SLAVEADDR, pdata, size);

	return ret;
}

/**
 * @brief  MPU9250 Read word
 * @param
 * 		addr2read	[I] - MPU Slave address
 * 		pdata 		[O] - Data Buffer
 * 		size 		[I] - Data Buffer size
 * @retval ret - Return API value
 */
retType APP_MPU9250Read(uint8_t addr2read, uint8_t * pdata, uint16_t size){

	retType ret = API_OK;

	if(size <= 0) ret = API_ERROR;
	if(ret != API_OK) return ret;

	ret |= DEV_I2CWrite(MPU9250_SLAVEADDR, &addr2read, 1);
	ret |= DEV_I2CRead(MPU9250_SLAVEADDR, pdata, size);

	return ret;

}

/**
 * @brief  MPU9250 Initializer function
 * @param
 * 		void
 * @retval ret - Return API value
 */
retType APP_MPU9250Init(void){

	retType ret = API_OK;

	ret |= DEV_I2CIsReady(MPU9250_SLAVEADDR);
	if(ret != API_OK) return ret;

	ret |= APP_MPU9250Write(MPU9250_PWR_MGMT_1, (uint8_t*)0x0, 1);
	if(ret != API_OK) return ret;
	ret |= APP_MPU9250Write(MPU9250_PWR_MGMT_1, (uint8_t*)0x1, 1);
	if(ret != API_OK) return ret;
	ret |= APP_MPU9250Write(MPU9250_GYRO_CONFIG, (uint8_t*)0x8, 1);
	ret |= APP_MPU9250Write(MPU9250_ACCEL_CONFIG_1, (uint8_t*)0x8, 1);
	ret |= APP_MPU9250Write(MPU9250_ACCEL_CONFIG_2, (uint8_t*)0x5, 1);
	if(ret != API_OK) return ret;
	ret |= APP_MPU9250Write(MPU9250_CONFIG_AD, (uint8_t*)0x5, 1);
	return ret;

}

/**
 * @brief  MPU9250 Read Gyroscope value per Axis
 * @param
 * 		gyro [O] - Gyroscope structure with axes
 * @retval ret - Return API value
 */
retType APP_MPU9250ReadGyro(axis_t * gyro){

	retType ret = API_OK;
	uint16_t aux_x = 0;
	uint16_t aux_y = 0;
	uint16_t aux_z = 0;

	ret |= APP_MPU9250Read(MPU9250_GYRO_XOUT_H, (uint8_t*)&aux_x, 2);
	ret |= APP_MPU9250Read(MPU9250_GYRO_YOUT_H, (uint8_t*)&aux_y, 2);
	ret |= APP_MPU9250Read(MPU9250_GYRO_ZOUT_H, (uint8_t*)&aux_z, 2);

	ret |= gyro_convert(aux_x, &(gyro->x));
	ret |= gyro_convert(aux_y, &(gyro->y));
	ret |= gyro_convert(aux_z, &(gyro->z));
	return ret;
}

/**
 * @brief  MPU9250 Read Accelerometer value per Axis
 * @param
 * 		accl [O] - Accelerometer structure with axes
 * @retval ret - Return API value
 */
retType APP_MPU9250ReadAccl(axis_t * accl){

	retType ret = API_OK;
	uint16_t aux_x = 0;
	uint16_t aux_y = 0;
	uint16_t aux_z = 0;

	ret |= APP_MPU9250Read(MPU9250_ACCEL_XOUT_H, (uint8_t*)&aux_x, 2);
	ret |= APP_MPU9250Read(MPU9250_ACCEL_YOUT_H, (uint8_t*)&aux_y, 2);
	ret |= APP_MPU9250Read(MPU9250_ACCEL_ZOUT_H, (uint8_t*)&aux_z, 2);

	ret |= accl_convert(aux_x, &(accl->x));
	ret |= accl_convert(aux_y, &(accl->y));
	ret |= accl_convert(aux_z, &(accl->z));
	return ret;
}

/**
 * @brief  MPU9250 Read Temperature value
 * @param
 * 		temp [O] - Temperature value
 * @retval ret - Return API value
 */
retType APP_MPU9250ReadTemp(uint16_t * temp){

	retType ret = API_OK;
	uint16_t aux_temp = 0;

	ret |= APP_MPU9250Read(MPU9250_TEMP_OUT_H, (uint8_t*)&aux_temp, 2);

	ret |= temp_convert(aux_temp, temp);
	return ret;
}

/**
 * @brief  MPU9250 Gyroscope convert value (Intern function)
 * @param
 * 		axis [I] - Axis value to convert
 * 		paxis [O] - Value converted
 * @retval ret - Return API value
 */
static retType gyro_convert(uint16_t axis, uint16_t * paxis){

	retType ret = API_OK;

	*paxis = axis;
	return ret;
}

/**
 * @brief  MPU9250 Accelerometer convert value (Intern function)
 * @param
 * 		axis [I] - Axis value to convert
 * 		paxis [O] - Value converted
 * @retval ret - Return API value
 */
static retType accl_convert(uint16_t axis, uint16_t * paxis){

	retType ret = API_OK;

	*paxis = axis;
	return ret;
}

/**
 * @brief  MPU9250 Temperature convert value (Intern function)
 * @param
 * 		axis [I] - Axis value to convert
 * 		paxis [O] - Value converted
 * @retval ret - Return API value
 */
static retType temp_convert(uint16_t temp, uint16_t * ptemp){

	retType ret = API_OK;

	*ptemp = (temp - 0)/321 + 21;
	return ret;
}
