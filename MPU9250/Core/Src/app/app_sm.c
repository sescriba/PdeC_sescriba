/**
 ******************************************************************************
 * @file     Core/Src/app/app_sm.c
 * @author  Santiago Escriba
 * @brief   File with State Machine definition.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "app_sm.h"

/* Private define ------------------------------------------------------------*/
#define READ_TIME 1000

/* Private variables ---------------------------------------------------------*/
State_t states;
State_t new_state;
MPU9250_t read_buff;
bool_t it_i2c;
bool_t first_time;
ttimer_t idle;

/* Private function prototypes -----------------------------------------------*/
static retType print_string(MPU9250_t * data);

/* Exposed Function  ---------------------------------------------------------*/
/**
 * @brief  SM Initialization
 * @param
 * 		void
 * @retval ret - Return API value
 */
retType APP_SMInit(void){

	retType ret = API_OK;

	states = SM_INIT;
	ret |= DEV_TimerInit(&idle, READ_TIME);
	return ret;
}

/**
 * @brief  SM Set and work according current state
 * @param
 * 		void
 * @retval ret - Return API value
 */
retType APP_SMProccess(void){

	retType ret = API_OK;
	bool_t done = false;

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
				new_state = SM_READGYRO;
				states = SM_IDLE;
			}
			else{
				states = SM_ERROR;
				break;
			}
			break;
		case SM_READGYRO:
			ret |= APP_MPU9250ReadGyro(&read_buff.gyro);
			if(ret != API_OK){
				states = SM_ERROR;
				break;
			}
			new_state = SM_READACCL;
			states = SM_IDLE;
			break;
		case SM_READACCL:
			ret |= APP_MPU9250ReadAccl(&read_buff.accl);
			if(ret != API_OK){
				states = SM_ERROR;
				break;
			}
			new_state = SM_READTEMP;
			states = SM_IDLE;
			break;
		case SM_READTEMP:
			ret |= APP_MPU9250ReadTemp(&read_buff.temp);
			if(ret != API_OK){
				states = SM_ERROR;
				break;
			}
			new_state = SM_PRINT;
			states = SM_IDLE;
			break;
		case SM_PRINT:
			ret |= print_string(&read_buff);
			if(ret == API_OK){
				new_state = SM_READGYRO;
				states = SM_IDLE;
			}
			break;
		case SM_IDLE:
			ret |= DEV_TimerRead(&idle, &done);
			if(done == true){
				states = new_state;
			}
			break;
		case SM_ERROR:
		default:
			ret = API_ERROR;
			break;
	}
	return ret;
}

/**
 * @brief  Print a string with MPU9250 information via UART
 * @param
 * 		data	[I] - MPU9250 Data to print
 * @retval ret - Return API value
 */
static retType print_string(MPU9250_t * data){

	retType ret = API_OK;
	uint8_t buff[256] = {0};
	uint8_t value[5] = {0};
	uint8_t str[] = "Data returned: ";
	uint8_t str_gyro[] = "\nGyroscope: ";
	uint8_t str_accl[] = "\nAccelerometer: ";
	uint8_t str_temp[] = "\nTemperature: ";
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
	strcat(buff, "*C\n\n");

	for(i = 0; i<256; i++){
		if(buff[i] == '\0') return ret;
		DEV_UARTSendChar(&buff[i]);
	}
	return ret;
}
