
#include "Bluetooth.h"
#include "string.h"

Bluetooth_Handler *Helper_HBluQueue;


#define TURN_LEFT			'l'
#define TURN_RIGHT			'r'



void MOV_voidSetComm(Bluetooth_Handler *Copy_HBluQueue)
{
	Helper_HBluQueue = Copy_HBluQueue;

	/* Create a queue to store data that u wanna receive */
	Copy_HBluQueue->ReceivingQueue = queue_new();

}



tenuErrorStatus MOV_enuReceiveData(Bluetooth_Handler *Copy_HBluQueue)
{
	tenuErrorStatus RetStatus = E_OK;
	if(Copy_HBluQueue != NULL)
	{
		HAL_UART_Receive_IT(Copy_HBluQueue->huartX, &Copy_HBluQueue->ReceivingingData[0], sizeof(uint8_t));
	}
	else{RetStatus = E_NOK_PARAM_OUT_OF_RANGE;}
	return RetStatus;
}




void MOV_enuFrameBuffering(Bluetooth_Handler *Copy_HBluQueue)
{
	uint8_t Loc_arrSpeedChars[4] ={0}, Loc_arrAngleChars[4] ={0}, loc_u8Count_1 =1, loc_u8Count_2 =0;
	Stored_Data_t Loc_strStoredData;

	/* Allocate the speed char indicator ex. ('R') */
	Loc_strStoredData.SpeedChar = Copy_HBluQueue->Buffer[0];

	/* Copy Speed Chars for converting to integer value */
	while(Copy_HBluQueue->ReceivingingData[loc_u8Count_1] != BLUETOOTH_ANGLE_CHAR)
	{Loc_arrSpeedChars[loc_u8Count_1 - 1] = Copy_HBluQueue->Buffer[loc_u8Count_1]; ++loc_u8Count_1;}

	/* Allocate the speed value */
	Loc_strStoredData.SpeedVal = atoi(Loc_arrSpeedChars);

	/* Allocate the angle char indicator ex. ('A') */
	Loc_strStoredData.AngleChar = Copy_HBluQueue->Buffer[loc_u8Count_1];

	while(Copy_HBluQueue->Buffer[loc_u8Count_1 + 1] != BLUETOOTH_END_CHAR)
	{Loc_arrAngleChars[loc_u8Count_2] = Copy_HBluQueue->Buffer[loc_u8Count_1 + 1]; ++loc_u8Count_1; ++loc_u8Count_2;}

	/* Allocate the Angle value (uint16_t) */
	Loc_strStoredData.AngleVal = atoi(Loc_arrAngleChars);

	/* Data buffering */
	queue_push_tail_nonVolatile(Copy_HBluQueue->ReceivingQueue , &Loc_strStoredData, sizeof(Loc_strStoredData));


}


void BLUTH_RxCpltProcess(UART_HandleTypeDef *huart)
{
	static uint8_t  Loc_u8CallingNum =0;
	Loc_u8CallingNum++;

	if(Helper_HBluQueue->ReceivingingData[Loc_u8CallingNum - 1] == BLUETOOTH_END_CHAR)
	{
		strcpy((uint8_t *)Helper_HBluQueue->Buffer, (uint8_t *)Helper_HBluQueue->ReceivingingData);
		Loc_u8CallingNum =0;
		MOV_voidRxFrameCallback();
	}

	HAL_UART_Receive_IT(huart, &Helper_HBluQueue->ReceivingingData[Loc_u8CallingNum], sizeof(uint8_t));

}




__weak void MOV_voidRxFrameCallback(void)
{


}




