/********************************************************************************
 * @file           : Bluetooth.h														*
 * @author         : Salem Elfaidy												*
 * @brief          : Contains  APIs to control the car movement.				*
 *******************************************************************************/

#ifndef BLUETOOTH_BLUETOOTH_H_
#define BLUETOOTH_BLUETOOTH_H_

/*------------------------------------ Includes Start --------------------------------------*/
#include "Common/STD_Types.h"
//#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal.h"
#include "Queue/queue.h"
#include <stdlib.h>
/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/

#define BLUETOOTH_END_CHAR						'E'
#define BLUETOOTH_SPEED_CHAR					'R'
#define BLUETOOTH_ANGLE_CHAR					'A'

/*-------------------------- Macro• Functions Declarations Start ---------------------------*/

/*-------------------------- Macro• Functions Declarations End -----------------------------*/

/*------------------------------ Data type Declarations Start ------------------------------*/

typedef struct
{
	UART_HandleTypeDef *huartX;
	Queue_t *ReceivingQueue;
	uint8_t ReceivingingData[10];
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
tenuErrorStatus MOV_enuReceiveData(Bluetooth_Handler *Copy_HBluQueue);


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
void MOV_enuFrameBuffering(Bluetooth_Handler *Copy_HBluQueue);


void MOV_voidRxFrameCallback(void);

/*------------------------- Software Interfaces Declarations End ----------------------------*/



/*
 * Private.....***************************************************************************************************
 * Private.........***********************************************************************************************
 * Private................****************************************************************************************
 */

/*---------------------------------------------------------------------------------------------------------------*/



#endif /* BLUETOOTH_BLUETOOTH_H_ */
