/********************************************************************************
 * @file           : MOTOR_MDD10A.h												*
 * @author         : Salem Elfaidy  -- 2023/10/15								*
 * @brief          : Contains  APIs to control motor driver "MDD10A".			*
 *******************************************************************************/

#ifndef MOTOR_MDD10A_MOTOR_MDD10A_H_
#define MOTOR_MDD10A_MOTOR_MDD10A_H_


/*------------------------------------ Includes Start --------------------------------------*/
#include "Common/STD_Types.h"
#include "stm32f4xx.h"
//#include "stm32f4xx_hal_tim.h"
//#include "stm32f4xx_hal_gpio.h"
/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/
/** @defgroup GPIO_port_define GPIO ports define
  * @{
  */
#define GPIO_PORT_A                      	GPIOA
#define GPIO_PORT_B	                  	 	GPIOB
#define GPIO_PORT_C       		         	GPIOC
#define GPIO_PORT_D                      	GPIOD
#define GPIO_PORT_E                      	GPIOE
#define GPIO_PORT_H                      	GPIOH

/*-------------------------- Macro• Functions Declarations Start ---------------------------*/

/*-------------------------- Macro• Functions Declarations End -----------------------------*/

/*------------------------------ Data type Declarations Start ------------------------------*/
typedef struct
{
	TIM_HandleTypeDef *htimX;			 /*!< Specifies the timer handler that you set to feed the motor channel
	 	 	 	 	 	 	 	 	 	   with the PWM. */

	TIM_OC_InitTypeDef *sConfigOC;		 /*!< Specifies the TIM Output Compare Configuration Structure definition.
	 	 	 	 	 	 	 	 	 	   You need only to define the timer OCmode to "TIM_OCMODE_PWM1/2".
	 	 	 	 	 	 	 	 	 	   and the timer OCpolarity to "TIM_OCPOLARITY_HIGH/LOW" */

	GPIO_TypeDef *Motor_Dir_Port;        /*!< Specifies the GPIO port that connected to the Motor pin direction.
                           	   	   	   	   This parameter can be any value of @ref GPIO_port_define */

	uint16_t Motor_Dir_Pin;       		 /*!< Specifies the GPIO pins that connected to the motor pin direction.
                           	   	   	   	   This parameter can be any value of GPIO_PIN_0 to GPIO_PIN_15 */

	uint16_t Motor_Channel;       		 /*!< Specifies the TIM channel that connected to the Motor driver.
                           	   	   	   	   This parameter can be any value of TIM_CHANNEL_1 to TIM_CHANNEL_4 */
}MOTOR_HandleTypeDef;
/*------------------------------ Data type Declarations End --------------------------------*/


/*------------------------- Software Interfaces Declarations Start --------------------------*/

/**
 * @Function Name: MOTOR_voidInitMotor
 *
 * @Description: Initializes the motor configuration based on what was provided in the "MOTOR_MDD10A_Lcfg.c" file.
 *
 * @Arguments:
 * 			void: Takes no arguments.
 *
 * @Return:
 * 			void: Returns nothing.
 **/
void MOTOR_voidInitMotor(void);


/**
 * @Function Name: MOTOR_voidMoveForward
 *
 * @Description: Moves the vehicle forward with a specific speed.
 *
 * @Arguments:
 * 			1. uint8_t Copy_u8MotorSpeed [in]:
 * 					Specifies the motor speed.
 * 				 	The motor speed can be specified in the range from 0 (minimum speed) to 100 (maximum speed).
 * 				 	Note: If a number greater than 100 is provided, the function returns an error state.
 * 			2. MOTOR_HandleTypeDef *MOTOR_cfg [in]:
 * 					A pointer to a struct containing the motor configurations
 * 					(Port and Pin Number) to control motor direction and Timer handler.
 *
 * @Return:
 * 			tenuErrorStatus: Returns an error status indicating whether the function executed correctly or not.
 **/
tenuErrorStatus MOTOR_voidMoveForward(uint8_t Copy_u8MotorSpeed, MOTOR_HandleTypeDef *MOTOR_cfg);


/**
 * @Function Name: MOTOR_voidMoveBackward
 *
 * @Description: Moves the vehicle backward with a specific speed.
 *
 * @Arguments:
 * 			1. uint8_t Copy_u8MotorSpeed [in]:
 * 					Specifies the motor speed.
 * 				 	The motor speed can be specified in the range from 0 (minimum speed) to 100 (maximum speed).
 * 				 	Note: If a number greater than 100 is provided, the function returns an error state.
 * 			2. MOTOR_HandleTypeDef *MOTOR_cfg [in]:
 * 					A pointer to a struct containing the motor configurations
 * 					(Port and Pin Number) to control motor direction and Timer handler.
 *
 * @Return:
 * 			tenuErrorStatus: Returns an error status indicating whether the function executed correctly or not.
 **/
tenuErrorStatus MOTOR_voidMoveBackward(uint8_t Copy_u8MotorSpeed, MOTOR_HandleTypeDef *MOTOR_cfg);



/**
 * @Function Name: MOTOR_voidTurnLeft
 *
 * @Description: Turn the vehicle left with a specific speed and angle.
 *
 * @Arguments:
 * 			1. uint8_t Copy_u8MotorSpeed [in]:
 * 					Specify the motor speed for turning left.
 * 				 	The motor speed can be set in the range from 0 (minimum speed) to 100 (maximum speed).
 * 				 	Note: If a number greater than 100 is provided, the function returns an error state.
 * 			2. uint8_t Copy_u8TurnAngle [in]:
 * 					Specify the angle for turning left.
 * 					The angle should be in degrees (0 to 360).
 * 			3. MOTOR_HandleTypeDef *MOTOR_1_cfg [in]:
 * 					A pointer to the struct containing motor configurations (Port and Pin Number)
 * 					to control the motor direction and Timer handler for motor 1.
 * 			4. MOTOR_HandleTypeDef *MOTOR_2_cfg [in]:
 * 					A pointer to the struct containing motor configurations (Port and Pin Number)
 * 					to control the motor direction and Timer handler for motor 2.
 *
 * @Return:
 * 			tenuErrorStatus: Returns an error status indicating whether the function executed correctly or not.
 **/

tenuErrorStatus MOTOR_voidTurnLeft(uint8_t Copy_u8MotorSpeed, uint8_t Copy_u8TurnAngle, MOTOR_HandleTypeDef *MOTOR_1_cfg, MOTOR_HandleTypeDef *MOTOR_2_cfg);



/**
 * @Function Name: MOTOR_voidTurnRight
 *
 * @Description: Turn the vehicle right with a specific speed and angle.
 *
 * @Arguments:
 * 			1. uint8_t Copy_u8MotorSpeed [in]:
 * 					Specify the motor speed for turning left.
 * 				 	The motor speed can be set in the range from 0 (minimum speed) to 100 (maximum speed).
 * 				 	Note: If a number greater than 100 is provided, the function returns an error state.
 * 			2. uint8_t Copy_u8TurnAngle [in]:
 * 					Specify the angle for turning right.
 * 					The angle should be in degrees (0 to 360).
 * 			3. MOTOR_HandleTypeDef *MOTOR_1_cfg [in]:
 * 					A pointer to the struct containing motor configurations (Port and Pin Number)
 * 					to control the motor direction and Timer handler for motor 1.
 * 			4. MOTOR_HandleTypeDef *MOTOR_2_cfg [in]:
 * 					A pointer to the struct containing motor configurations (Port and Pin Number)
 * 					to control the motor direction and Timer handler for motor 2.
 *
 * @Return:
 * 			tenuErrorStatus: Returns an error status indicating whether the function executed correctly or not.
 **/
tenuErrorStatus MOTOR_voidTurnRight(uint8_t Copy_u8MotorSpeed, uint8_t Copy_u8TurnAngle, MOTOR_HandleTypeDef *MOTOR_1_cfg, MOTOR_HandleTypeDef *MOTOR_2_cfg);



/**
 * @Function Name: MOTOR_voidStopMoving
 *
 * @Description: Stops the vehicle.
 *
 * @Arguments:
 * 			1. MOTOR_HandleTypeDef *MOTOR_cfg [in]:
 * 					A pointer to a struct containing the motor configurations
 * 					(Port and Pin Number) to control motor direction and Timer handler.
 *
 * @Return:
 * 			void: Returns nothing.
 **/
void MOTOR_voidStopMoving(MOTOR_HandleTypeDef *MOTOR_cfg);


/**
 * @Function Name: HAL_TIM_PMM_DutyCycle
 *
 * @Description: Generates PWM with a desired duty cycle for general purpose.
 *               Note: This function is not necessary to drive the motor driver "MDD10A".
 *
 * @Arguments:
 * 			1. MOTOR_HandleTypeDef *MOTOR_cfg [in]:
 * 					A pointer to a struct containing the motor configurations
 * 					(Port and Pin Number) to control motor direction and Timer handler.
 * 			2. uint8_t Copy_u8DutyPercentage [in]:
 * 					Specifies the PWM duty cycle.
 * 				 	The PWM duty cycle can be specified in the range from 0 (minimum duty cycle) to 100 (maximum duty cycle).
 * 				 	Note: If a number greater than 100 is provided, the function returns an error state.
 *
 * @Return:
 * 			tenuErrorStatus: Returns an error status indicating whether the function executed correctly or not.
 **/
tenuErrorStatus HAL_TIM_PMM_DutyCycle(MOTOR_HandleTypeDef *MOTOR_cfg, uint8_t Copy_u8DutyPercentage);

/*------------------------- Software Interfaces Declarations End ----------------------------*/



/*
 * Private.....***************************************************************************************************
 * Private.........***********************************************************************************************
 * Private................****************************************************************************************
 */
#define  MOTOR_POLARITY_AND_PWM_MODE_CONDITION(POLARITY, PWM_MODE)		((POLARITY == TIM_OCPOLARITY_HIGH)&&\
																		(PWM_MODE == TIM_OCMODE_PWM1))||\
																		((POLARITY == TIM_OCPOLARITY_LOW)&&\
																		(PWM_MODE == TIM_OCMODE_PWM2))

/*---------------------------------------------------------------------------------------------------------------*/


#endif /* MOTOR_MDD10A_MOTOR_MDD10A_H_ */
