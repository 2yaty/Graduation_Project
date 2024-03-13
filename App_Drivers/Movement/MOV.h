/********************************************************************************
 * @file           : MOV.h														*
 * @author         : Salem Elfaidy												*
 * @brief          : Contains  APIs to control the car movement.				*
 *******************************************************************************/

#ifndef MOVEMENT_MOV_H_
#define MOVEMENT_MOV_H_


/*------------------------------------ Includes Start --------------------------------------*/
#include "Common/STD_Types.h"
#include "MOTOR_MDD10A/MOTOR_MDD10A_Lcfg.h"
#include "Queue/queue.h"
//#include "stm32f4xx_hal.h"
/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/

#define MOV_END_CHAR						'E'
#define MOV_SPEED_CHAR					'R'
#define MOV_ANGLE_CHAR					'A'

/*-------------------------- Macro• Functions Declarations Start ---------------------------*/

/*-------------------------- Macro• Functions Declarations End -----------------------------*/

/*------------------------------ Data type Declarations Start ------------------------------*/


typedef struct
{
	MOTOR_HandleTypeDef *hmotor_1;
	MOTOR_HandleTypeDef *hmotor_2;
	Queue_t *SourceBuffer;

}MOV_Handler;
/*------------------------------ Data type Declarations End --------------------------------*/


/*------------------------- Software Interfaces Declarations Start --------------------------*/

/**
 * @Function Name: MOTOR_voidDRIVER_INIT
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
void MOV_voidInitMovement(void);



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
 * 			2.Motor_Dir_Cfg_t *MOTOR_cfg[in]:
 * 					This is a pointer to stuct that contains the motor configurations
 * 					((Port and Pin Number) to control motor direction -> Dir pin in "MDD10A" board,
 * 					and Timer Channel index -> PWM pin in "MDD10A" board).
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/
tenuErrorStatus MOV_enuMovementHandler(MOV_Handler *Copy_HBluQueue);



/*------------------------- Software Interfaces Declarations End ----------------------------*/



/*
 * Private.....***************************************************************************************************
 * Private.........***********************************************************************************************
 * Private................****************************************************************************************
 */

/*---------------------------------------------------------------------------------------------------------------*/


#endif /* MOVEMENT_MOV_H_ */
