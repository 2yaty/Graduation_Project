/*
 * Lidar.c
 *
 *  Created on: Feb 20, 2024
 *      Author: HP
 */
/************************** Includes start  *****************************************/
#include <string.h>
#include "Lidar.h"


/************************** Includes end  ********************************************/

/************************** static functions prototypes start *****************************************/
static uint8_t u8ConvertDecToHex(uint8_t Copy_u8DecValue)                       ;
static uint8_t u8CalculateChecksum(uint8_t *Copy_u8frame, uint8_t Copy_u8length);
static tenuErrorStatus Lidar_tenuSavaSettings(Lidar_Handle *Copy_hLidar)        ;
/************************** static functions prototypes end *******************************************/


/**
 * @Function Name: Lidar_voidInit
 *
 * @Description: This function initializes the Lidar.
 *
 * @Arguments:
 * 			Lidar_Handle & UART_HandleTypeDef :
 * 					take the Lidar_Handle --> lidar structure to access the huartX that used in UART_Rx function.
 * 					And initializes the Copy_hLidar->huartX with UART_HandleTypeDef--> huartX.
 *
 * @Return:
 * 			return nothing.
 **/
void Lidar_voidInit(Lidar_Handle *Copy_hLidar,UART_HandleTypeDef *huartX)
{

	Copy_hLidar->huartX = huartX;
	Copy_hLidar->LidarFrame = (uint8_t*) malloc(9*sizeof(uint8_t));
}

/**
 * @Function Name: Lidar_tenuEnableOutput
 *
 * @Description: This function enables the Lidar output data(if it disabled).
 *
 * @Arguments:
 * 			Lidar_Handle:
 * 					take the Lidar_Handle --> lidar structure to access the huartX that used in UART_Tx function.
 *
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/

tenuErrorStatus Lidar_tenuEnableOutput(Lidar_Handle *Copy_hLidar)
{
	//tenuErrorStatus Loc_tenuReturn = E_NOK ;
	uint8_t Loc_EnableCommanad[] = {0x5A, 0x05 ,0x07, 0x01, 0x67} ;
	//uint8_t Loc_au8Response[5];

	/* Send the command */
	HAL_UART_Transmit_DMA_IT(Copy_hLidar->huartX, Loc_EnableCommanad , sizeof(Loc_EnableCommanad));
	/* Now--> Save the settings to confirm the command by sending the save setting command */
	Lidar_tenuSavaSettings();

/*
	// Receive the response from the lidar
	HAL_UART_Receive_DMA(Copy_hLidar->huartX , Loc_au8Response , sizeof(Loc_au8Response));


	// Check the response
	if(memcmp(Loc_au8Response, Loc_EnableCommanad, sizeof(Loc_au8Response)) == 0)
	{
       Loc_tenuReturn = E_OK ;
    }
    else
    {
       Loc_tenuReturn = E_NOK ;
    }

    return Loc_tenuReturn ;

*/
}

/**
 * @Function Name: Lidar_tenuDisableOutput
 *
 * @Description: This function disable the Lidar output data.
 *
 * @Arguments:
 * 			Lidar_Handle:
 * 					take the Lidar_Handle --> lidar structure to access the huartX that used in UART_Tx function.
 *
 * @Return:
 * 		   tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/
tenuErrorStatus Lidar_tenuDisableOutput(Lidar_Handle *Copy_hLidar)
{
	//tenuErrorStatus Loc_tenuReturn = E_NOK ;
	uint8_t Loc_au8DisableCommanad[] = {0x5A, 0x05 ,0x07, 0x00, 0x66} ;
	//uint8_t Loc_au8Response[5];

	/* Send the command */
	HAL_UART_Transmit_DMA_IT(Copy_hLidar->huartX , Loc_au8DisableCommanad , sizeof(Loc_au8DisableCommanad));

	/* Now--> Save the settings to confirm the command by sending the save setting command */
	Lidar_tenuSavaSettings();
/*
	// Receive the response from the lidar
	HAL_UART_Receive_DMA( Copy_hLidar->huartX, Loc_au8Response , sizeof(Loc_au8Response));


	// Check the response
	if(memcmp(Loc_au8Response, Loc_au8DisableCommanad, sizeof(Loc_au8Response)) == 0)
	{
	    Loc_tenuReturn = E_OK ;
	}
	else
	{
		Loc_tenuReturn = E_NOK ;
	}

	return Loc_tenuReturn ;
*/
}

/**
 * @Function Name: Lidar_voidTriggerDetection
 *
 * @Description: Trigger detection functionality in a LiDAR system typically involves
 * 				 the ability to detect specific events or conditions in the environment based on the LiDAR data
 *
 * @Arguments:
 * 			Lidar_Handle:
 * 					take the Lidar_Handle --> lidar structure to access the huartX that used in UART_Tx function.
 * @Return:
 * 			void:
 * 					return nothing.
 **/
void Lidar_voidTriggerDetection(Lidar_Handle *Copy_hLidar)
{
		uint8_t Loc_au8TriggerDetectionComannd[] = {0x5A, 0x04 ,0x04, 0x62} ;
		/* Send the command */
		HAL_UART_Transmit_DMA_IT(Copy_hLidar->huartX , Loc_au8TriggerDetectionComannd , sizeof(Loc_au8TriggerDetectionComannd));

		/* Now--> Save the settings to confirm the command by sending the save setting command */
		Lidar_tenuSavaSettings();
}


/**
 * @Function Name: Lidar_tenuSetFrameRate
 *
 * @Description: This function set a frame rate to the sensor (from 0 to 250 Hz).
 *
 * @Arguments:
 * 			Lidar_Handle:
 * 					take the Lidar_Handle --> lidar structure to access the huartX that used in UART_Tx function & FrameRate
 * 					to choose frame rate from 0 to 250 Hz.
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.

 **/
tenuErrorStatus Lidar_tenuSetFrameRate(Lidar_Handle *Copy_hLidar)
{
	//tenuErrorStatus Loc_tenuReturn = E_NOK ;
	//uint8_t Loc_au8Response[6] ;

	// convert the decimal value into hex :
	uint8_t Loc_u8HexRate ;
	Loc_u8HexRate = u8ConvertDecToHex(Copy_hLidar->FrameRate);
	//                                            frame rate value         Checksum before calculating it
	uint8_t Loc_au8frame[] = {0x5A, 0x06, 0x03 , Loc_u8HexRate , 0x00   ,         0x00};

	// calculate the checksum value :
	uint8_t Loc_u8Checksum = u8CalculateChecksum(Loc_au8frame, sizeof(Loc_au8frame) );

	// converting the checksum into hex :
	uint8_t Loc_u8HexChecksum = u8ConvertDecToHex(Loc_u8Checksum);


	// now the Checksum after calculating it
	 Loc_au8frame[5] =   Loc_u8HexChecksum ;

	// the frame is ready now and can be sent
	HAL_UART_Transmit_DMA_IT(Copy_hLidar->huartX , Loc_au8frame , sizeof(Loc_au8frame));

	/* Now--> Save the settings to confirm the command by sending the save setting command */
	Lidar_tenuSavaSettings();

	/*
	// Receive the response from the lidar
	HAL_UART_Receive_DMA( Copy_hLidar->huartX, Loc_au8Response , sizeof(Loc_au8Response));

    // check the response from the lidar
	if(memcmp(Loc_au8Response, Loc_au8frame, sizeof(Loc_au8Response)) == 0)
	{
		Loc_tenuReturn = E_OK ;
	}
	else
	{
		Loc_tenuReturn = E_NOK ;
	}

    return Loc_tenuReturn ;
*/
}

/**
 * @Function Name: Lidar_voidReceiveData
 *
 * @Description: This function get 9 bytes [0:8] data from lidar --> the distance reading is included inside these 9 bytes
 * 				 Byte2  Dist_L distance value low 8 bits
 *               Byte3  Dist_H distance value high 8 bits
 *
 * @Arguments:
 * 			Lidar_Handle:
 * 					take the Lidar_Handle --> lidar structure to access the huartX that used in UART_Rx function.
 * @Return:
 * 		   void:
 * 					return nothing.
 **/
void Lidar_voidReceiveData(Lidar_Handle *Copy_hLidar)
{
	HAL_UART_Receive_DMA_IT(Copy_hLidar->huartX, Copy_hLidar->LidarFrame, sizeof(Copy_hLidar->LidarFrame));
	/*
	 * Suppose now that the data is received and the interrupt is fired.
	 * Now we need a function that service this interrupt.
	 * This function implemented below
	 * */
}

/**
 * @Function Name: Lidar_RxFrameCallBack
 *
 * @Description: This function is a weak function that indicates that the frame is received.
 *               The function is called in the UART_CallBack in the main file.
 *
 * @Arguments:
 *         Lidar_Handle *Copy_hLidar:
 *                  Takes the Lidar_Handle to access the huartX that is used in UART_Rx function.
 * @Return:
 *         void: Returns nothing.
 **/
__attribute__((weak)) void Lidar_RxFrameCallBack(void)
{

    // HAL_UART_Receive_DMA(Copy_hLidar->huartX, Copy_hLidar->LidarFrame, sizeof(Copy_hLidar->LidarFrame));
}


/**
 * @Function Name: Lidar_voidGetDistance
 *
 * @Description: this function extracts the distance from the received frame from lidar.
 *
 *
 * @Arguments:
 * 			Lidar_Handle:
 * 					take the Lidar_Handle --> lidar structure to access the Copy_hLidar->Distance and Copy_hLidar->LidarFrame .
 * @Return:
 * 		   void:
 * 					return nothing.
 **/
void    Lidar_voidGetDistance(Lidar_Handle *Copy_hLidar)
{
	Copy_hLidar->Distance = (Copy_hLidar->LidarFrame[3] << 8) | Copy_hLidar->LidarFrame[2];
	// Now the  Distance variable in Lidar_Handle object has the distance measurement from the lidar

	// TODO: move extracting the distance to the dma callback and the distance should be ready right away
}

static tenuErrorStatus Lidar_tenuSavaSettings(Lidar_Handle *Copy_hLidar)
{
	uint8_t Loc_au8SaveSettingsFrame[] = {0x5A, 0x04, 0x11, 0x6F};
	uint8_t Loc_au8SettingsResponseFrame[] = {0x5A, 0x05, 0x11, 0x00, 0x6F}  ;
	uint8_t Loc_au8SettingsResponse[5]                                       ;

	// Send the LIDAR_SAVE_SETTINGS frame --> Loc_au8SaveSettingsFrame
	HAL_UART_Transmit_DMA_IT(Copy_hLidar->huartX , Loc_au8SaveSettingsFrame , sizeof(Loc_au8SaveSettingsFrame));

	/*
	// Receive the response frame from the lidar in Loc_au8SettingsResponse
	HAL_UART_Receive_DMA( Copy_hLidar->huartX, Loc_au8SettingsResponse , sizeof(Loc_au8SettingsResponse));

	// Check the received frame with comparing it with Loc_au8SettingsResponseFrame
	if(memcmp(Loc_au8SettingsResponse, Loc_au8SettingsResponseFrame, sizeof(Loc_au8SettingsResponse)) == 0)
	{
		Loc_tenuReturn = E_OK ;
	}
    else
    {
      	Loc_tenuReturn = E_NOK ;
    }
	*/

}

static uint8_t u8CalculateChecksum(uint8_t *Copy_u8frame, uint8_t Copy_u8length)
{
    uint8_t Loc_u8sum = 0;

    // Sum all bytes except start byte and checksum byte
    for (uint8_t i = 1; i < Copy_u8length - 1; i++)
    {
        Loc_u8sum += Copy_u8frame[i];
    }

    // Take the least significant byte of the sum and complement it
    uint8_t Loc_u8checksum = ~Loc_u8sum;

    return Loc_u8checksum;
}

static uint8_t u8ConvertDecToHex(uint8_t Copy_u8DecValue)
{
	uint8_t Loc_u8Result ;
	if (Copy_u8DecValue < 10)
	{
		// If decimal value is less than 10, return the corresponding hexadecimal value
		Loc_u8Result = Copy_u8DecValue ;
	}
	else
	{
		// If decimal value is 10 or greater, return the corresponding hexadecimal value (A-F)
		Loc_u8Result = Copy_u8DecValue - 10 + 0x0A;
    }

	return Loc_u8Result ;

}




/* omar */


