
#include "MOV.h"

extern UART_HandleTypeDef huart6;
#define TURN_LEFT			'l'
#define TURN_RIGHT			'r'

void ControlMotion(MOV_Handler *Copy_HBluQueue, uint8_t Speed, uint8_t Angle, uint8_t Direction);



void MOV_voidInitMovement(void)
{
	MOTOR_voidInitMotor();
}



tenuErrorStatus MOV_enuMovementHandler(MOV_Handler *Copy_HBluQueue)
{
	uint8_t Loc_u8RecData_1, Loc_u8Speed, Loc_u8Angle;
	tenuErrorStatus RetStatus = E_OK;

	if(deQueue(Copy_HBluQueue->SourceBuffer, &Loc_u8RecData_1) != -1)
	{
		while((Loc_u8RecData_1 != TURN_LEFT) && (Loc_u8RecData_1 != TURN_RIGHT))
		{
			if(Loc_u8RecData_1 == MOV_SPEED_CHAR)
			{
				deQueue(Copy_HBluQueue->SourceBuffer, &Loc_u8Speed);
				deQueue(Copy_HBluQueue->SourceBuffer, &Loc_u8RecData_1); // get 'A' in Loc_u8RecData_1
			}
			else if(Loc_u8RecData_1 == MOV_ANGLE_CHAR)
			{
				deQueue(Copy_HBluQueue->SourceBuffer, &Loc_u8Angle);
				deQueue(Copy_HBluQueue->SourceBuffer, &Loc_u8RecData_1);
				ControlMotion(Copy_HBluQueue, Loc_u8Speed, Loc_u8Angle, Loc_u8RecData_1);
				RetStatus = E_PROCESS_COMPLETE;
			}
		}
	}
	else{RetStatus = E_NOK_PARAM_OUT_OF_RANGE;}
	return RetStatus;
}



void ControlMotion(MOV_Handler *Copy_HBluQueue, uint8_t Speed, uint8_t Angle, uint8_t Direction)
{
//	uint8_t x = 'S';
//	//HAL_UART_Transmit_IT(&huart6, &x, sizeof(uint8_t));
//	//HAL_UART_Transmit_IT(&huart6, &Speed, sizeof(uint8_t));
//	x = 'A';
//	//HAL_UART_Transmit(&huart6, &x, sizeof(uint8_t), 2);
//	HAL_UART_Transmit(&huart6, &Angle, sizeof(uint8_t), 2);
//	//HAL_UART_Transmit_IT(&huart6, &Direction, sizeof(uint8_t));
	if(Angle < 10)
	{
		MOTOR_voidMoveForward(Speed, Copy_HBluQueue->hmotor_1);
		MOTOR_voidMoveForward(Speed, Copy_HBluQueue->hmotor_2);
	}
	else if(Angle > 170)
	{
		MOTOR_voidMoveBackward(Speed, Copy_HBluQueue->hmotor_1);
		MOTOR_voidMoveBackward(Speed, Copy_HBluQueue->hmotor_2);
		//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	}
	else
	{
		if(Direction == TURN_RIGHT){MOTOR_voidTurnRight(Speed, Angle, Copy_HBluQueue->hmotor_1, Copy_HBluQueue->hmotor_2);}
		else if(Direction == TURN_LEFT){MOTOR_voidTurnLeft(Speed, Angle, Copy_HBluQueue->hmotor_1, Copy_HBluQueue->hmotor_2);}
	}

}




