#ifndef FCW_APP_H
#define FCW_APP_H

/*------------------------------------ Includes Start --------------------------------------*/
#include "Common/STD_Types.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_dma.h"
/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/
#define MAX_TIME_IN_SEC   100.0f

#define LOW_WARNING_TH_TIME      3.0f
#define MID_WARNING_TH_TIME      2.0f
#define HIGH_WARNING_TH_TIME     1.0f
/*------------------------------- Macro Declarations End------------------------------------*/


/*------------------------------ Data type Declarations Start ------------------------------*/
typedef struct
{
	uint8_t Speed        ;
	float AccX           ;
	float Distance       ;
	float CalculatedTime ;

}FCW_Handle;

typedef enum 
{
	No_Warning     ,
	High_Warning   ,
	Middle_Warning ,
	Low_Warning     
}enum_FC_Warnings_t ;


/*------------------------------ Data type Declarations End --------------------------------*/

/*------------------------- Software Interfaces Declarations Start --------------------------*/
/**
 * @Function Name: FCW_u8TimeToCollision
 *
 * @Description: This function calculates the time that the car model will take to reach an object
 *               using the 2nd motion equation.
 *
 * @Arguments:
 * 			  Speed , Distance , Acc :
 * 			  Takes the car speed, car acceleration, and the distance of the lidar
 * 			  between the car and the detected object.
 *
 * @Return:
 * 			float : The calculated time in seconds.
 **/
float FCW_u8TimeToCollision(uint8_t Copy_u8Speed , float Copy_u8Distance , float Copy_u8AccX);

/**
 * @Function Name: FCW_enuIsWarning
 *
 * @Description: This function decides if there is a warning or not according to
 * 				 the given time.
 *
 * @Arguments:
 * 			  Calculated time :
 * 			  takes the calculated time from FCW_u8TimeToCollision to decide a warning or not.
 *
 * @Return:
 * 			enum_FC_Warnings_t : Returns an enum to show if there is an error or not and if there is an error, 
 * 			it determine its warning level.
 **/
enum_FC_Warnings_t FCW_enuIsWarning(float Copy_u8CalculatedTime);




/*------------------------- Software Interfaces Declarations End ----------------------------*/


#endif
