/*
 * port.h
 *
 *  Created on: Sep 25, 2022
 *      Author: Santiago
 */

#ifndef DEV_INC_PORT_H_
#define DEV_INC_PORT_H_

retType DEV_InitI2C(void);
retType DEV_DeInitI2C(void);
retType DEV_WriteI2C(uint16_t addr, uint8_t * pdata, uint16_t size);
retType DEV_ReadI2C(uint16_t addr, uint8_t * pdata, uint16_t size);


#endif /* DEV_INC_PORT_H_ */
