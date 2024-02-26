/****************************************************************************************
 * @file           : MPU_Lcfg.c												*
 * @author         : Salem&Omar  15/12/2023													*
 * @brief          : Contains the needed data to initialize the MPU sensor.				*
 ***************************************************************************************/



#include "MPU.h"

extern I2C_HandleTypeDef hi2c1;
MPU_HandleTypeDef hMPU;

void MPU_SetCfg(void)
{
	hMPU.hi2c = &hi2c1;
	hMPU.GyroSampleRate = MPU_GYRO_RATE_1K;
	hMPU.GyroFullScale = MPU_GYRO_SCALE_250;
	hMPU.AccelFullScale = MPU_ACCEL_SCALE_2g;
	hMPU.MPU_Address = MPU_AD0_0;
	hMPU.DataRequestState = FIRST_REQUEST;
	hMPU.state = MPU_STATE_RESET;
	hMPU.GPIO_INT_PinNum = GPIO_PIN_0;

}





