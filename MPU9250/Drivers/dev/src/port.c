/*
 * port.c
 *
 *  Created on: 22 sep. 2022
 *      Author: Santiago
 */


#include "port.h"

#define I2C_CLOCKSPEED 100000
#define I2C_OWNADDRESS1 0
#define I2C_TIMEOUT 0xFFFF

I2C_HandleTypeDef  hi2c;

retType DEV_I2CInit(void){

	retType ret = API_OK;
	hi2c.Instance = I2C2;
	hi2c.Init.ClockSpeed = I2C_CLOCKSPEED;
	hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c.Init.OwnAddress1 = I2C_OWNADDRESS1;
	hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;


	ret |= HAL_I2C_Init(&hi2c);
	return ret;

}

retType DEV_I2CDeInit(void){

	retType ret = API_OK;

	ret |= HAL_I2C_DeInit(&hi2c);
	return ret;

}

retType DEV_I2CWrite(uint16_t slave_addr, uint8_t * pdata, uint16_t size){

	retType ret = API_OK;

	ret |= HAL_I2C_Master_Transmit(&hi2c, slave_addr, pdata, size, I2C_TIMEOUT);
	return ret;


}

retType DEV_I2CRead(uint16_t slave_addr, uint8_t * pdata, uint16_t size){

	retType ret = API_OK;

	ret |= HAL_I2C_Master_Receive(&hi2c, slave_addr, pdata, size, I2C_TIMEOUT);
	return ret;

}

retType DEV_I2CIsReady(uint16_t slave_addr){

	retType ret = API_OK;
	ret = HAL_I2C_IsDeviceReady(&hi2c, slave_addr, 2, 1000);
	return ret;
}
//Aca viene todo lo de I2C
//Definir Macros
//funciones que utilicen I2C (read/write byte)
//configurar el I2C
//usar funciones de la HAL de I2c
//Iniciar la interrupciones I2C
