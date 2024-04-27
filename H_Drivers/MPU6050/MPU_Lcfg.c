/****************************************************************************************
 * @file           : MPU_Lcfg.c												*
 * @author         : Salem&Omar 														*
 * @brief          : Contains the needed data to initialize the MPU sensor.				*
 ***************************************************************************************/
/*
 * Notes:
 * 		(##) The objects that created in this file used in other files with the same name,
 * 				So you have't to change any of them.
 * 		(##) The prescaler and period (overflow value) were selected with specific initial values
 * 				according to the clock source that feeds the timer (APB bus) was (16 MHZ) divided by 1.
 *
 * 				(&&) Initial values with (16 MHZ) divided by 1 (&&)
 * 				(++) htimX.Init.Prescaler = 15;  Note: the register value -> ( 1 + prescaler value),
 * 					   then the clock here divided by 16 not 15.
 * 				(++) htimX.Init.Period = 49;  -> with 50 micro seconds period u get (20 KHZ), that is
 * 						the needed frequency to drive the motor driver "MDD10A".
 * 		(##) You can select any pin and port to control the motor direction, But don't forget
 * 				to initialize this pin in GPIO initialization. Also the channel pin .
 */


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





