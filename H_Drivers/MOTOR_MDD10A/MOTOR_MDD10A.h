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
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_gpio.h"
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
 * @Description: This function initializes the timer PWM depending on configuration you provided in
 * 					@ref MOTOR_MDD10A_Lcfg.c file.
 *
 * @Arguments:
 * 			void:
 * 					take nothing.
 *
 * @Return:
 * 			void: return nothing.
 **/
void MOTOR_voidInitMotor(void);


/**
 * @Function Name: MOTOR_voidMoveForward
 *
 * @Description: Move motor forward with specific speed.
 *
 * @Arguments:
 * 			1.uint8_t Copy_u8MotorSpeed[in]:
 * 					Specify the motor speed.
 * 				 	You can specify the motor speed in range 0 (as min speed) to 100 (as max speed)
 * 				 	Note: in case u Insert number more than 100, the function returns error state.
 * 			2.MOTOR_HandleTypeDef *MOTOR_cfg[in]:
 * 					This is a pointer to stuct that contains the motor configurations
 * 					((Port and Pin Number) to control motor direction -> Dir pin in "MDD10A" board,
 * 					and Timer Channel index -> PWM pin in "MDD10A" board).
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/
tenuErrorStatus MOTOR_voidMoveForward(uint8_t Copy_u8MotorSpeed, MOTOR_HandleTypeDef *MOTOR_cfg);


/**
 * @Function Name: MOTOR_voidMoveBackward
 *
 * @Description: Move motor backward with specific speed.
 *
 * @Arguments:
 * 			1.uint8_t Copy_u8MotorSpeed[in]:
 * 					Specify the motor speed.
 * 				 	You can specify the motor speed in range 0 (as min speed) to 100 (as max speed)
 * 				 	Note: in case u Insert number more than 100, the function returns error state.
 * 			2.MOTOR_HandleTypeDef *MOTOR_cfg[in]:
 * 					This is a pointer to stuct that contains the motor configurations
 * 					((Port and Pin Number) to control motor direction -> Dir pin in "MDD10A" board,
 * 					and Timer Channel index -> PWM pin in "MDD10A" board).
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/
tenuErrorStatus MOTOR_voidMoveBackward(uint8_t Copy_u8MotorSpeed, MOTOR_HandleTypeDef *MOTOR_cfg);


/**
 * @Function Name: MOTOR_voidMoveBackward
 *
 * @Description: Move motor backward with specific speed.
 *
 * @Arguments:
 * 			1.uint8_t Copy_u8MotorSpeed[in]:
 * 					Specify the motor speed.
 * 				 	You can specify the motor speed in range 0 (as min speed) to 100 (as max speed)
 * 				 	Note: in case u Insert number more than 100, the function returns error state.
 * 			2.MOTOR_HandleTypeDef *MOTOR_cfg[in]:
 * 					This is a pointer to stuct that contains the motor configurations
 * 					((Port and Pin Number) to control motor direction -> Dir pin in "MDD10A" board,
 * 					and Timer Channel index -> PWM pin in "MDD10A" board).
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/
tenuErrorStatus MOTOR_voidTurnLeft(uint8_t Copy_u8MotorSpeed, uint8_t Copy_u8TurnAngle, MOTOR_HandleTypeDef *MOTOR_1_cfg, MOTOR_HandleTypeDef *MOTOR_2_cfg);


/**
 * @Function Name: MOTOR_voidMoveBackward
 *
 * @Description: Move motor backward with specific speed.
 *
 * @Arguments:
 * 			1.uint8_t Copy_u8MotorSpeed[in]:
 * 					Specify the motor speed.
 * 				 	You can specify the motor speed in range 0 (as min speed) to 100 (as max speed)
 * 				 	Note: in case u Insert number more than 100, the function returns error state.
 * 			2.MOTOR_HandleTypeDef *MOTOR_cfg[in]:
 * 					This is a pointer to stuct that contains the motor configurations
 * 					((Port and Pin Number) to control motor direction -> Dir pin in "MDD10A" board,
 * 					and Timer Channel index -> PWM pin in "MDD10A" board).
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/
tenuErrorStatus MOTOR_voidTurnRight(uint8_t Copy_u8MotorSpeed, uint8_t Copy_u8TurnAngle, MOTOR_HandleTypeDef *MOTOR_1_cfg, MOTOR_HandleTypeDef *MOTOR_2_cfg);


/**
 * @Function Name: MOTOR_voidStopMoving
 *
 * @Description: Stop the motor.
 *
 * @Arguments:
 * 			1.MOTOR_HandleTypeDef *MOTOR_cfg[in]:
 * 					This is a pointer to stuct that indicates to the motor u wanna stop.
 * 					((Port and Pin Number) to control motor direction -> Dir pin in "MDD10A" board,
 * 					and Timer Channel index -> PWM pin in "MDD10A" board).
 * @Return:
 * 			void: return nothing.
 **/
void MOTOR_voidStopMoving(MOTOR_HandleTypeDef *MOTOR_cfg);


/**
 * @Function Name: HAL_TIM_PMM_DutyCycle
 *
 * @Description: Generate PWM with desired duty cycle for (General Purpose).
 * 				 Note: this function isn't necessary to drive the motor driver "MDD10A".
 *
 * @Arguments:
 * 			1.uint8_t Copy_u8DutyPercentage[in]:
 * 					Specify the PWM duty cycle.
 * 				 	You can specify the PWM duty cycle in range 0 (as min duty cycle) to 100 (as max duty cycle)
 * 				 	Note: in case u Insert number more than 100, the function returns error state.
 * 			2.uint8_t Copy_u8OutChannel[in]:
 * 					Specify the channel u wanna generate PWM from.
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/
tenuErrorStatus HAL_TIM_PMM_DutyCycle( MOTOR_HandleTypeDef *MOTOR_cfg, uint8_t Copy_u8DutyPercentage);

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
