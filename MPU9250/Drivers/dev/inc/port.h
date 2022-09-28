/*
 * port.h
 *
 *  Created on: Sep 25, 2022
 *      Author: Santiago
 */

#ifndef DEV_INC_PORT_H_
#define DEV_INC_PORT_H_

#include "types.h"
#include "stm32f4xx_hal_i2c.h"

retType DEV_I2CInit(void);
retType DEV_I2CDeInit(void);
retType DEV_I2CWrite(uint16_t slave_addr, uint8_t * pdata, uint16_t size);
retType DEV_I2CRead(uint16_t slave_addr, uint8_t * pdata, uint16_t size);
retType DEV_I2CIsReady(uint16_t slave_addr);


#endif /* DEV_INC_PORT_H_ */
