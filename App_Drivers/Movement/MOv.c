
#include "MOV.h"


Bluetooth_Handler *Helper_HBluQueue;




void MOV_voidSetComm(Bluetooth_Handler *Copy_HBluQueue)
{
	Helper_HBluQueue = Copy_HBluQueue;
//	/* Create a queue to store data that u wanna send */
//	Copy_HBluQueue->SendingQueue = createQueue;

	/* Create a queue to store data that u wanna receive */
	Copy_HBluQueue->ReceivingQueue = createQueue;

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
	tenuErrorStatus RetStatus = E_OK;
	if(Copy_HBluQueue != NULL)
	{
		HAL_UART_Receive_DMA(huart, (uint8_t *) &Copy_HBluQueue->ReceivingingData, sizeof(uint8_t));
	}
	else{RetStatus = E_NOK_PARAM_OUT_OF_RANGE;}
	return RetStatus;
}




tenuErrorStatus MOV_enuMovementHandler(Bluetooth_Handler *Copy_HBluQueue)
{
	uint8_t *Loc_u8RecData;
	deQueue(Copy_HBluQueue->ReceivingQueue, Loc_u8RecData);
	tenuErrorStatus RetStatus = E_OK;
	if(Copy_HBluQueue != NULL)
	{
		switch (*Loc_u8RecData)
		{
			case MOV_STOP_CHAR:

				break;
			case MOV_FORWARD_CHAR:

				break;
			case MOV_BACKWARD_CHAR:

				break;
			case MOV_LEFT_CHAR:

				break;
			case MOV_RIGHT_CHAR:

				break;
			default:
				break;
		}
	}
	else{RetStatus = E_NOK_PARAM_OUT_OF_RANGE;}
	return RetStatus;
}




void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	enQueue(Helper_HBluQueue->ReceivingQueue, Helper_HBluQueue->ReceivingingData);
}



void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{



}


