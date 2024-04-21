#ifndef FCW_APP_H
#define FCW_APP_H

/*------------------------------------ Includes Start --------------------------------------*/
#include "Common/STD_Types.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_dma.h"
/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/
/*------------------------------- Macro Declarations End------------------------------------*/


/*------------------------------ Data type Declarations Start ------------------------------*/
typedef struct
{
	uint8_t Speed        ;
	float AccX           ;
	float Distance       ;
	float CalculatedTime ;

}FCW_Handle;

FCW_Handle FCW_Data ;
/*------------------------------ Data type Declarations End --------------------------------*/

/*------------------------- Software Interfaces Declarations Start --------------------------*/
/**
 * @Function Name: FCW_Task
 *
 * @Description: This task alerts the driver whenever there is an object
 * 				 in the front of the car.
 *
 * @Arguments:
 * 			  void :  takes nothing.
 * @Return:
 * 			void : Returns nothing.
 **/
void FCW_Task(void);


/*------------------------- Software Interfaces Declarations End ----------------------------*/


#endif
