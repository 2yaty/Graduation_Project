
#include "MOV.h"

uint32_t i;
Bluetooth_Handler *Helper_HBluQueue;


#define TURN_LEFT			'l'
#define TURN_RIGHT			'r'


void ControlMotion(uint8_t Speed, uint8_t Angle, uint8_t Direction);

void MOV_voidSetComm(Bluetooth_Handler *Copy_HBluQueue)
{
	Helper_HBluQueue = Copy_HBluQueue;
	MOTOR_voidInitMotor();
//	/* Create a queue to store data that u wanna send */
//	Copy_HBluQueue->SendingQueue = createQueue;

	/* Create a queue to store data that u wanna receive */
	struct Queue* q = createQueue();
	Copy_HBluQueue->ReceivingQueue = q;

}




tenuErrorStatus MOV_enuSendData(Bluetooth_Handler *Copy_HBluQueue, UART_HandleTypeDef *huart, uint8_t *Copy_pData, uint8_t Copy_u8Datasize)
{
	tenuErrorStatus RetStatus = E_OK;
	if(Copy_HBluQueue != NULL)
	{
		HAL_UART_Transmit_DMA(huart, Copy_pData, Copy_u8Datasize);
	}
	else{RetStatus = E_NOK_PARAM_OUT_OF_RANGE;}
	return RetStatus;
}




tenuErrorStatus MOV_enuReceiveData(Bluetooth_Handler *Copy_HBluQueue, UART_HandleTypeDef *huart)
{

	static uint8_t Loc_u8Count =0;
	tenuErrorStatus RetStatus = E_OK;
	if (Copy_HBluQueue->state == MOV_FRAME_COMPLETED) {Loc_u8Count =0;}
	if(Copy_HBluQueue != NULL)
	{
		i++;
		Copy_HBluQueue->state = MOV_FRAME_IN_RECEIVE;
		HAL_UART_Receive_IT(huart, &Copy_HBluQueue->ReceivingingData[Loc_u8Count], sizeof(uint8_t));
	}
	else{RetStatus = E_NOK_PARAM_OUT_OF_RANGE;}
	Loc_u8Count++;
	return RetStatus;
}




tenuErrorStatus MOV_enuMovementHandler(Bluetooth_Handler *Copy_HBluQueue)
{
	uint8_t Loc_u8RecData_1, Loc_u8Speed, Loc_u8Angle;
	tenuErrorStatus RetStatus = E_OK;

	if(deQueue(Copy_HBluQueue->ReceivingQueue, &Loc_u8RecData_1) != -1)
	{
		while((Loc_u8RecData_1 != TURN_LEFT) && (Loc_u8RecData_1 != TURN_RIGHT))
		{
			if(Loc_u8RecData_1 == 'R')
			{
				deQueue(Copy_HBluQueue->ReceivingQueue, &Loc_u8Speed);
				deQueue(Copy_HBluQueue->ReceivingQueue, &Loc_u8RecData_1); // get 'A' in Loc_u8RecData_1
			}
			else if(Loc_u8RecData_1 == 'A')
			{
				deQueue(Copy_HBluQueue->ReceivingQueue, &Loc_u8Angle);
				deQueue(Copy_HBluQueue->ReceivingQueue, &Loc_u8RecData_1);
				ControlMotion(Loc_u8Speed, Loc_u8Angle, Loc_u8RecData_1);
				RetStatus = E_PROCESS_COMPLETE;
			}
		}
	}
	else{RetStatus = E_NOK_PARAM_OUT_OF_RANGE;}
	return RetStatus;
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	static uint8_t  Loc_u8CallingNum =0;
	if(Helper_HBluQueue->ReceivingingData[Loc_u8CallingNum] == MOV_END_CHAR)
	{
		uint8_t arrTemp[4], temp1, count1 =1, count2 =0;
		uint16_t temp2;
		while(Helper_HBluQueue->ReceivingingData[count1] != 'A'){arrTemp[count1 - 1] = Helper_HBluQueue->ReceivingingData[count1]; ++count1;}
		enQueue(Helper_HBluQueue->ReceivingQueue, Helper_HBluQueue->ReceivingingData[0]);
		temp1 = atoi(arrTemp);
		enQueue(Helper_HBluQueue->ReceivingQueue, temp1);
		enQueue(Helper_HBluQueue->ReceivingQueue, Helper_HBluQueue->ReceivingingData[count1]);
		while(Helper_HBluQueue->ReceivingingData[count1 +1] != MOV_END_CHAR){arrTemp[count2] = Helper_HBluQueue->ReceivingingData[count1+1]; ++count1; ++count2;}
		temp2 = atoi(arrTemp);
		if ((temp2 >= 90)&&(temp2 < 270))
		{
			enQueue(Helper_HBluQueue->ReceivingQueue, temp2 - 90);
			enQueue(Helper_HBluQueue->ReceivingQueue, TURN_LEFT);
		}
		else if (temp2 >= 270)
		{
			enQueue(Helper_HBluQueue->ReceivingQueue, temp2 - 180);
			enQueue(Helper_HBluQueue->ReceivingQueue, TURN_RIGHT);
		}
		else if ((temp2 >= 0)&&(temp2 < 90))
		{
			enQueue(Helper_HBluQueue->ReceivingQueue, 90 - temp2);
			enQueue(Helper_HBluQueue->ReceivingQueue, TURN_RIGHT);
		}

		Helper_HBluQueue->state = MOV_FRAME_COMPLETED;
		Loc_u8CallingNum =0;
		MOV_voidRxFrameCallback();
		return;
	}

	MOV_voidRxDataCallback();
	Loc_u8CallingNum++;
}




void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{


}


__weak void MOV_voidRxDataCallback(void)
{

}

__weak void MOV_voidRxFrameCallback(void)
{


}


void ControlMotion(uint8_t Speed, uint8_t Angle, uint8_t Direction)
{
	if((Angle < 10))
	{
		MOTOR_voidMoveForward(Speed, Helper_HBluQueue->hmotor_1);
		MOTOR_voidMoveForward(Speed, Helper_HBluQueue->hmotor_2);
	}
	else if((Angle > 170))
	{
		MOTOR_voidMoveBackward(Speed, Helper_HBluQueue->hmotor_1);
		MOTOR_voidMoveBackward(Speed, Helper_HBluQueue->hmotor_2);
	}
	else
	{
		if(Direction == TURN_RIGHT){MOTOR_voidTurnRight(Speed, Angle, Helper_HBluQueue->hmotor_1, Helper_HBluQueue->hmotor_2);}
		else if(Direction == TURN_LEFT){MOTOR_voidTurnLeft(Speed, Angle, Helper_HBluQueue->hmotor_1, Helper_HBluQueue->hmotor_2);}
	}

}




