
#include "MOV.h"



#define MOV_END_CHAR					'E'
#define MOV_SPEED_CHAR					'R'
#define MOV_ANGLE_CHAR					'A'
#define TURN_LEFT						'l'
#define TURN_RIGHT						'r'
#define MOV_STRAIGHT_ANGLE_RANGE		 10


osSemaphoreId_t* mov_Semaphore;

void ControlMotion(Task_MOV_Data *Copy_HBluQueue, Stored_Data_t *Copy_PstrStoredData);



void MOV_Init_Task(Bluetooth_Handler *hbluetooth ,osSemaphoreId_t* MOV_Semaphore)
{
	/* Init HW */
	MOTOR_voidInitMotor();
	BLUTH_voidSetComm(hbluetooth);

	if (MOV_Semaphore == NULL)
	{
	    /* Semaphore object not created, handle failure */
		//osError("Failed to create semaphore");
		return;
	}

	mov_Semaphore = MOV_Semaphore;

	/* Start receiving process in background */
	BLUTH_enuReceiveData(hbluetooth);
}



void MOV_Task(void *argument)
{
	Task_MOV_Data *pMOV = (Task_MOV_Data *)argument;
	Stored_Data_t Loc_PstrStoredData;

	for(;;)
	{

		/* Wait for data to be ready, assuming ISR will release semaphore */
		osSemaphoreAcquire(*mov_Semaphore, osWaitForever);

		/* Buffer the data in the required format after receiving completes */
		Loc_PstrStoredData = BLUTH_enuFrameBuffering(pMOV->h_bluetooth);

		/* Use the deceived data to control the car movement */
		ControlMotion(pMOV, &Loc_PstrStoredData);

		osDelay(40);
	}


}



void BLUTH_voidRxFrameCallback(void)
{
	osSemaphoreRelease(*mov_Semaphore);
}





void ControlMotion(Task_MOV_Data *Copy_HBluQueue, Stored_Data_t *Copy_PstrStoredData)
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
		if(Loc_u8Dir == TURN_RIGHT)
		{
			MOTOR_voidTurnRight(Copy_PstrStoredData->SpeedVal, Loc_u8Angle, Copy_HBluQueue->hmotor_1, Copy_HBluQueue->hmotor_2);
		}
		else if(Loc_u8Dir == TURN_LEFT)
		{
			MOTOR_voidTurnLeft(Copy_PstrStoredData->SpeedVal, Loc_u8Angle, Copy_HBluQueue->hmotor_1, Copy_HBluQueue->hmotor_2);
		}
	}

}




