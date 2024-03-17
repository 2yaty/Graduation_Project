
#include "MOV.h"

#define TURN_LEFT			'l'
#define TURN_RIGHT			'r'

void ControlMotion(MOV_Handler *Copy_HBluQueue, Stored_Data_t *Copy_PstrStoredData);



void MOV_voidInitMovement(void)
{
	MOTOR_voidInitMotor();
}



tenuErrorStatus MOV_enuMovementHandler(MOV_Handler *Copy_HBluQueue)
{
	tenuErrorStatus RetStatus = E_OK;

	/* Check if the queue is empty */
	if(queue_is_empty(Copy_HBluQueue->SourceBuffer) == 0)
	{
		/* Get the data from the buffer */
		Stored_Data_t *Loc_PstrStoredData = queue_pop_head(Copy_HBluQueue->SourceBuffer);

		ControlMotion(Copy_HBluQueue, Loc_PstrStoredData);

		/* Free the heap location that u allocated the data in */
		free(Loc_PstrStoredData);
		RetStatus = E_PROCESS_COMPLETE;
	}
	else{RetStatus = E_NOK_PARAM_OUT_OF_RANGE;}

	return RetStatus;
}



void ControlMotion(MOV_Handler *Copy_HBluQueue, Stored_Data_t *Copy_PstrStoredData)
{
	uint8_t Loc_u8Angle, Loc_u8Dir;

	/* Allocate the Angle value (scaling) and the direction char */
	if ((Copy_PstrStoredData->AngleVal >= 180)&&(Copy_PstrStoredData->AngleVal <= 360))
	{
		Loc_u8Angle = (360 - Copy_PstrStoredData->AngleVal);
		Loc_u8Dir  = TURN_LEFT;
	}
	else if ((Copy_PstrStoredData->AngleVal >= 0)&&(Copy_PstrStoredData->AngleVal < 180))
	{
		Loc_u8Angle = Copy_PstrStoredData->AngleVal;
		Loc_u8Dir  = TURN_RIGHT;
	}

	/* Handle the car movement according the angle, direction and speed */
	if(Loc_u8Angle < MOV_STRAIGHT_ANGLE_RANGE)
	{
		MOTOR_voidMoveForward(Copy_PstrStoredData->SpeedVal, Copy_HBluQueue->hmotor_1);
		MOTOR_voidMoveForward(Copy_PstrStoredData->SpeedVal, Copy_HBluQueue->hmotor_2);
	}
	else if(Loc_u8Angle > (180 - MOV_STRAIGHT_ANGLE_RANGE))
	{
		MOTOR_voidMoveBackward(Copy_PstrStoredData->SpeedVal, Copy_HBluQueue->hmotor_1);
		MOTOR_voidMoveBackward(Copy_PstrStoredData->SpeedVal, Copy_HBluQueue->hmotor_2);
	}
	else
	{
		if(Loc_u8Dir == TURN_RIGHT){MOTOR_voidTurnRight(Copy_PstrStoredData->SpeedVal, Loc_u8Angle, Copy_HBluQueue->hmotor_1, Copy_HBluQueue->hmotor_2);}
		else if(Loc_u8Dir == TURN_LEFT){MOTOR_voidTurnLeft(Copy_PstrStoredData->SpeedVal, Loc_u8Angle, Copy_HBluQueue->hmotor_1, Copy_HBluQueue->hmotor_2);}
	}

}




