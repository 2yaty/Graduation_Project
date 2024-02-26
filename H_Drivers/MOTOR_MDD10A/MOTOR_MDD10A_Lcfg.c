/****************************************************************************************
 * @file           : MOTOR_MDD10A_Lcfg.c												*
 * @author         : Salem Elfaidy	-- 2023/10/15										*
 * @brief          : Contains the needed data to initialize the motor driver "MDD10A".	*
 ***************************************************************************************/
/*
 *==============================================================================
 *                       ##### How to use this driver #####
 *==============================================================================
 * (##) Initialize a timer peripheral and extern its handler here like "extern TIM_HandleTypeDef htim3;".
 *      (++) htimX.Init.Prescaler = 15;  Note: the register value -> (1 + prescaler value),
 *              then the clock here divided by 16 not 15.
 *      (++) htimX.Init.Period = 49;  -> with 50 microseconds period you get (20 KHZ), which is
 *              the needed frequency to drive the motor driver "MDD10A".
 *      ---> Note: The prescaler and period (overflow value) were selected with specific initial values
 *      according to the clock source that feeds the timer (APB bus) was (16 MHz (internal CLK)) divided by 1.
 *
 * (##) Define the motor handler, Where the MDD10A can control two motors independently.
 *      (*) TIM_HandleTypeDef *htimX :
 *          Takes the timer handler that you set to feed the motor channel with the PWM.
 *      (*) TIM_OC_InitTypeDef *sConfigOC :
 *          Specifies the TIM Output Compare Configuration Structure definition.
 *          You need only to define the timer OCmode to "TIM_OCMODE_PWM1/2" and
 *          the timer OCpolarity to "TIM_OCPOLARITY_HIGH/LOW".
 *      (*) GPIO_TypeDef *Motor_Dir_Port :
 *          Specifies the GPIO port that is connected to the Motor pin direction.
 *          This parameter can be any value of @ref GPIO_port_define.
 *      (*) uint16_t Motor_Dir_Pin :
 *          Specifies the GPIO pins that are connected to the motor pin direction.
 *          This parameter can be any value of GPIO_PIN_0 to GPIO_PIN_15.
 *      (*) uint16_t Motor_Channel :
 *          Specifies the TIM channel that is connected to the Motor driver.
 *          This parameter can be any value of TIM_CHANNEL_1 to TIM_CHANNEL_4.
 *
 *      ---> You can select any pin and port to control the motor direction, but don't forget
 *          to initialize these pins in GPIO low level initialization, also the channel pins.
 *
 */






#include "MOTOR_MDD10A.h"

extern TIM_HandleTypeDef htim3;
MOTOR_HandleTypeDef MOTOR_1_cfg;
MOTOR_HandleTypeDef MOTOR_2_cfg;

/**
  * @brief  This function implemented to make the initialization process easier.
  *      	it called in "MOTOR_MDD10A.c" file.
  */
void MOTOR_cfg_Init(void)
{
	MOTOR_1_cfg.htimX = &htim3;
	MOTOR_2_cfg.htimX = &htim3;
	MOTOR_1_cfg.sConfigOC->OCMode = TIM_OCMODE_PWM1;
	MOTOR_2_cfg.sConfigOC->OCPolarity = TIM_OCPOLARITY_HIGH;
	MOTOR_1_cfg.Motor_Dir_Port = GPIO_PORT_B;
	MOTOR_1_cfg.Motor_Dir_Pin  = GPIO_PIN_1;
	MOTOR_1_cfg.Motor_Channel  = TIM_CHANNEL_1;
	MOTOR_2_cfg.Motor_Dir_Port = GPIO_PORT_B;
	MOTOR_2_cfg.Motor_Dir_Pin  = GPIO_PIN_2;
	MOTOR_2_cfg.Motor_Channel  = TIM_CHANNEL_2;

}




