/********************************************************************************
 * @file           : CortexM4_Core_NVIC.h										*
 * @author         : Salem Elfaidy												*
 * @brief          : Contains  APIs to control Led.								*
 *******************************************************************************/


#ifndef MPU_TASK_MPU_MOD_H_
#define MPU_TASK_MPU_MOD_H_

/*------------------------------------ Includes Start --------------------------------------*/
#include "MPU6050/MPU_Lcfg.h"
#include "cmsis_os.h"
#include "cJSON/cJSON.h"
/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/

#define MPU_TASK_PERIODICITY_ms			100

/*-------------------------- Macro• Functions Declarations Start ---------------------------*/

/*-------------------------- Macro• Functions Declarations End -----------------------------*/

/*------------------------------ Data type Declarations Start ------------------------------*/


typedef struct
{
	MPU_HandleTypeDef *h_MPU;
	float32_t AccelGyroDataBuffer[6];

}Task_MPU_Data;

/*------------------------------ Data type Declarations End --------------------------------*/


/*------------------------- Software Interfaces Declarations Start --------------------------*/


void MPU_Init_Task(osMessageQueueId_t* MPU_Tx_MsgQueue ,osSemaphoreId_t* MPU_Semaphore);
void MPU_Task(void *argument);


#endif /* MPU_TASK_MPU_MOD_H_ */
