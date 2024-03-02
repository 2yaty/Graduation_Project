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
#include "Queue.h"
#include <stdlib.h>
/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/


#define MOV_STOP_CHAR						'S'
#define MOV_FORWARD_CHAR					'F'
#define MOV_BACKWARD_CHAR					'B'
#define MOV_LEFT_CHAR						'L'
#define MOV_RIGHT_CHAR						'R'

#define MOV_END_CHAR						'E'

/*-------------------------- Macro• Functions Declarations Start ---------------------------*/

/*-------------------------- Macro• Functions Declarations End -----------------------------*/

/*------------------------------ Data type Declarations Start ------------------------------*/

typedef enum
{
	MOV_FRAME_IN_RECEIVE,
	MOV_FRAME_COMPLETED
}MOV_State_t;



typedef struct
{
	MOTOR_HandleTypeDef *hmotor_1;
	MOTOR_HandleTypeDef *hmotor_2;
	Queue_t *SendingQueue;
	Queue_t *ReceivingQueue;
	uint8_t SendingData;
	uint8_t ReceivingingData[10];
	MOV_State_t state;
}Bluetooth_Handler;
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
void MOV_voidSetComm(Bluetooth_Handler *Copy_HBluQueue);


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
tenuErrorStatus MOV_enuSendData(Bluetooth_Handler *Copy_HBluQueue, UART_HandleTypeDef *huart, uint8_t *Copy_pData, uint8_t Copy_u8Datasize);


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
tenuErrorStatus MOV_enuReceiveData(Bluetooth_Handler *Copy_HBluQueue, UART_HandleTypeDef *huart);


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
tenuErrorStatus MOV_enuMovementHandler(Bluetooth_Handler *Copy_HBluQueue);


void MOV_voidRxDataCallback(void);
void MOV_voidRxFrameCallback(void);

/*------------------------- Software Interfaces Declarations End ----------------------------*/



/*
 * Private.....***************************************************************************************************
 * Private.........***********************************************************************************************
 * Private................****************************************************************************************
 */

/*---------------------------------------------------------------------------------------------------------------*/


#endif /* MOVEMENT_MOV_H_ */
