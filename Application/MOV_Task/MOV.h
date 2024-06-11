/********************************************************************************
 * @file           : MOV.h														*
 * @author         : Salem Elfaidy												*
 * @brief          : Contains  APIs to control the car movement.				*
 *******************************************************************************/

#ifndef MOVEMENT_MOV_H_
#define MOVEMENT_MOV_H_


/*------------------------------------ Includes Start --------------------------------------*/
#include <Bluetooth/Bluetooth.h>
#include "MOTOR_MDD10A/MOTOR_MDD10A_Lcfg.h"
#include "cmsis_os.h"
//#include "stm32f4xx_hal.h"
/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/

#define MOV_TASK_PERIODICITY_ms			51

/*-------------------------- Macro• Functions Declarations Start ---------------------------*/

/*-------------------------- Macro• Functions Declarations End -----------------------------*/

/*------------------------------ Data type Declarations Start ------------------------------*/


typedef struct
{
	MOTOR_HandleTypeDef *hmotor_1;
	MOTOR_HandleTypeDef *hmotor_2;
	Bluetooth_Handler *h_bluetooth;

}Task_MOV_Data;
/*------------------------------ Data type Declarations End --------------------------------*/


/*------------------------- Software Interfaces Declarations Start --------------------------*/


void MOV_Init_Task(Bluetooth_Handler *hbluetooth ,osSemaphoreId_t* MOV_Semaphore);
void MOV_Task(void *argument);



/*------------------------- Software Interfaces Declarations End ----------------------------*/



/*
 * Private.....***************************************************************************************************
 * Private.........***********************************************************************************************
 * Private................****************************************************************************************
 */

/*---------------------------------------------------------------------------------------------------------------*/


#endif /* MOVEMENT_MOV_H_ */
