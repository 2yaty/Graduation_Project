/********************************************************************************
 * @file           : CortexM4_Core_NVIC.h										*
 * @author         : Salem Elfaidy												*
 * @brief          : Contains  APIs to control Led.								*
 *******************************************************************************/


#ifndef MPU_MODULE_MPU_MOD_H_
#define MPU_MODULE_MPU_MOD_H_

/*------------------------------------ Includes Start --------------------------------------*/
#include "MPU6050/MPU_Lcfg.h"

/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/

/*-------------------------- Macro• Functions Declarations Start ---------------------------*/

/*-------------------------- Macro• Functions Declarations End -----------------------------*/

/*------------------------------ Data type Declarations Start ------------------------------*/

typedef enum
{
	//TASK_MPU_DATA_NOT_REQUESTED,
	//TASK_MPU_DATA_REQUESTED,
	TASK_MPU_REQUESTE_DATA,
	TASK_MPU_DATA_READY,
	TASK_MPU_DONE

}Task_MPU_State;


typedef struct
{
	Task_MPU_State MPUTaskState;
	MPU_HandleTypeDef *h_MPU;
	float32_t AccelGyroDataBuffer[6];

}Task_MPU_Data;

/*------------------------------ Data type Declarations End --------------------------------*/


/*------------------------- Software Interfaces Declarations Start --------------------------*/

//void TASK_MPUInit(void *PvMPUInitData);

void TASK_MPU(void *PvMPUInitData);

#endif /* MPU_MODULE_MPU_MOD_H_ */
