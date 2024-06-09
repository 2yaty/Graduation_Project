/*
 * Lidar.h
 *
 *  Created on: Feb 20, 2024
 *      Author: HP
 */

#ifndef TF_LIDAR_LIDAR_H_
#define TF_LIDAR_LIDAR_H_

/*------------------------------------ Includes Start --------------------------------------*/
#include "Common/STD_Types.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_dma.h"
/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/
/** @defgroup GPIO_port_define GPIO ports define
  * @{
  */

/*-------------------------- Macro• Functions Declarations Start ---------------------------*/

/*-------------------------- Macro• Functions Declarations End -----------------------------*/

/*------------------------------ Data type Declarations Start ------------------------------*/
typedef struct
{
	UART_HandleTypeDef *huartX  ;
	uint8_t  Command            ;
	uint8_t  FrameRate          ;
	uint8_t  *LidarFrame        ;
	uint16_t Distance           ;
}Lidar_Handle;
/*------------------------------ Data type Declarations End --------------------------------*/


/*------------------------- Software Interfaces Declarations Start --------------------------*/

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
void Lidar_voidInit(Lidar_Handle *Copy_hLidar,UART_HandleTypeDef *huartX);
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
tenuErrorStatus Lidar_tenuEnableOutput(Lidar_Handle *Copy_hLidar);


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
tenuErrorStatus Lidar_tenuDisableOutput(Lidar_Handle *Copy_hLidar);


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
void Lidar_voidTriggerDetection(Lidar_Handle *Copy_hLidar);


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
tenuErrorStatus Lidar_tenuSetFrameRate(Lidar_Handle *Copy_hLidar);




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
void Lidar_voidReceiveData(Lidar_Handle *Copy_hLidar);



/**
 * @Function Name: Lidar_RxFrameCallBack
 *
 * @Description: This function is a weak function that indicates the frame is received.
 *               The function is called in the UART_CallBack in the main file.
 *
 * @Arguments:
 *         Lidar_Handle *Copy_hLidar:
 *                  Takes the Lidar_Handle to access the huartX that is used in UART_Rx function.
 * @Return:
 *         void: Returns nothing.
 **/
__attribute__((weak)) void Lidar_RxFrameCallBack(void);

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


/*------------------------- Software Interfaces Declarations End ----------------------------*/



/*
 * Private.....***************************************************************************************************
 * Private.........***********************************************************************************************
 * Private................****************************************************************************************
 */
/*---------------------------------------------------------------------------------------------------------------*/








#endif /* TF_LIDAR_LIDAR_H_ */
