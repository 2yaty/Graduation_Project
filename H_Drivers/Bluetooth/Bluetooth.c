
#include <Bluetooth/Bluetooth.h>
#include <string.h>



#define TURN_LEFT			'l'
#define TURN_RIGHT			'r'



void BLUTH_voidSetComm(Bluetooth_Handler *hbluetooth)
{

	/* Create a queue to store data that u wanna receive */
	hbluetooth->ReceivingQueue = queue_new();

}



tenuErrorStatus BLUTH_enuReceiveData(Bluetooth_Handler *hbluetooth)
{
	tenuErrorStatus RetStatus = E_OK;
	if(hbluetooth != NULL)
	{
		HAL_UART_Receive_IT(hbluetooth->huartX, &hbluetooth->ReceivingingData[0], sizeof(uint8_t));
	}
	else{RetStatus = E_NOK_PARAM_OUT_OF_RANGE;}
	return RetStatus;
}




Stored_Data_t BLUTH_enuFrameBuffering(Bluetooth_Handler *hbluetooth)
{
	uint8_t Loc_arrSpeedChars[4] ={0}, Loc_arrAngleChars[4] ={0}, loc_u8Count_1 =1, loc_u8Count_2 =0;
	Stored_Data_t Loc_strStoredData;

	/* Allocate the speed char indicator ex. ('R') */
	Loc_strStoredData.SpeedChar = hbluetooth->Buffer[0];

	/* Copy Speed Chars for converting to integer value */
	//TODO: Remember to replace "ReceivingingData" by "Buffer" after testing.
	while(hbluetooth->ReceivingingData[loc_u8Count_1] != BLUETOOTH_ANGLE_CHAR)
	{
		Loc_arrSpeedChars[loc_u8Count_1 - 1] = hbluetooth->Buffer[loc_u8Count_1];
		++loc_u8Count_1;
	}

	//todo:Loc_strStoredData.SpeedVal = atoi((char *)Loc_arrSpeedChars);
	/* Allocate the speed value */
	Loc_strStoredData.SpeedVal = atoi(Loc_arrSpeedChars);

	/* Allocate the angle char indicator ex. ('A') */
	Loc_strStoredData.AngleChar = hbluetooth->Buffer[loc_u8Count_1];

	while(hbluetooth->Buffer[loc_u8Count_1 + 1] != BLUETOOTH_END_CHAR)
	{
		Loc_arrAngleChars[loc_u8Count_2] = hbluetooth->Buffer[loc_u8Count_1 + 1];
		++loc_u8Count_1;
		++loc_u8Count_2;
	}

	/* Allocate the Angle value (uint16_t) */
	Loc_strStoredData.AngleVal = atoi(Loc_arrAngleChars);

	/* Data buffering */
	return Loc_strStoredData;

}


void BLUTH_RxCpltProcess(Bluetooth_Handler *hbluetooth)
{
	static uint8_t  Loc_u8CallingNum =0;
	Loc_u8CallingNum++;

	if(hbluetooth->ReceivingingData[Loc_u8CallingNum - 1] == BLUETOOTH_END_CHAR)
	{
		/* To avoid overwriting in case the receiving occurred before buffering */
		strcpy((uint8_t *)hbluetooth->Buffer, (uint8_t *)hbluetooth->ReceivingingData);
		Loc_u8CallingNum =0;
		BLUTH_voidRxFrameCallback();
	}

	HAL_UART_Receive_IT(hbluetooth->huartX, &hbluetooth->ReceivingingData[Loc_u8CallingNum], sizeof(uint8_t));

}




__weak void BLUTH_voidRxFrameCallback(void)
{


}




