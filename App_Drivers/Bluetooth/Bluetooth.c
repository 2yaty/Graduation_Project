
#include "Bluetooth.h"

uint32_t i;
Bluetooth_Handler *Helper_HBluQueue;


#define TURN_LEFT			'l'
#define TURN_RIGHT			'r'


void MOV_voidSetComm(Bluetooth_Handler *Copy_HBluQueue)
{
	Helper_HBluQueue = Copy_HBluQueue;

	/* Create a queue to store data that u wanna receive */
	Copy_HBluQueue->ReceivingQueue = createQueue();

}



tenuErrorStatus MOV_enuReceiveData(Bluetooth_Handler *Copy_HBluQueue)
{
	tenuErrorStatus RetStatus = E_OK;
	if(Copy_HBluQueue != NULL)
	{
		i++;
		HAL_UART_Receive_IT(Copy_HBluQueue->huartX, &Copy_HBluQueue->ReceivingingData[0], sizeof(uint8_t));
	}
	else{RetStatus = E_NOK_PARAM_OUT_OF_RANGE;}
	return RetStatus;
}




void MOV_enuFrameBuffering(Bluetooth_Handler *Copy_HBluQueue)
{
	uint8_t arrTemp_1[4] ={0}, arrTemp_2[4] ={0}, temp1, count1 =1, count2 =0;
	uint16_t temp2;
	while(Copy_HBluQueue->ReceivingingData[count1] != BLUETOOTH_ANGLE_CHAR){arrTemp_1[count1 - 1] = Copy_HBluQueue->ReceivingingData[count1]; ++count1;}
	enQueue(Copy_HBluQueue->ReceivingQueue, Copy_HBluQueue->ReceivingingData[0]);
	temp1 = atoi(arrTemp_1);
	enQueue(Copy_HBluQueue->ReceivingQueue, temp1);
	enQueue(Copy_HBluQueue->ReceivingQueue, Copy_HBluQueue->ReceivingingData[count1]);
	while(Copy_HBluQueue->ReceivingingData[count1 +1] != BLUETOOTH_END_CHAR){arrTemp_2[count2] = Copy_HBluQueue->ReceivingingData[count1+1]; ++count1; ++count2;}
	temp2 = atoi(arrTemp_2);
	if ((temp2 >= 90)&&(temp2 < 270))
	{
		enQueue(Copy_HBluQueue->ReceivingQueue, temp2 - 90);
		enQueue(Copy_HBluQueue->ReceivingQueue, TURN_LEFT);
	}
	else if (temp2 >= 270)
	{
		enQueue(Copy_HBluQueue->ReceivingQueue, temp2 - 180);
		enQueue(Copy_HBluQueue->ReceivingQueue, TURN_RIGHT);
	}
	else if ((temp2 >= 0)&&(temp2 < 90))
	{
		enQueue(Copy_HBluQueue->ReceivingQueue, 90 - temp2);
		enQueue(Copy_HBluQueue->ReceivingQueue, TURN_RIGHT);
	}

}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	static uint8_t  Loc_u8CallingNum =0;
	Loc_u8CallingNum++;
	if(Helper_HBluQueue->ReceivingingData[Loc_u8CallingNum - 1] == BLUETOOTH_END_CHAR)
	{
		Loc_u8CallingNum =0;
		MOV_voidRxFrameCallback();
		//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	}

	HAL_UART_Receive_IT(huart, &Helper_HBluQueue->ReceivingingData[Loc_u8CallingNum], sizeof(uint8_t));

}



__weak void MOV_voidRxFrameCallback(void)
{


}








