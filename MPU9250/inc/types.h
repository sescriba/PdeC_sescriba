/*
 * types.h
 *
 *  Created on: Sep 25, 2022
 *      Author: Santiago
 */

#ifndef INC_TYPES_H_
#define INC_TYPES_H_

/**
  * @brief  retType Status structures definition
  */
typedef enum
{
  API_OK       = 0x00U,
  API_ERROR    = 0x01U,
  API_BUSY     = 0x02U,
  API_TIMEOUT  = 0x03U
} retType;



#endif /* INC_TYPES_H_ */
