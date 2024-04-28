/********************************************************************************
 * @file           : CortexM4_Core_NVIC.h										*
 * @author         : Salem Elfaidy												*
 * @brief          : Contains  APIs to control Led.								*
 *******************************************************************************/


#ifndef MPU_MODULE_MPU_MOD_H_
#define MPU_MODULE_MPU_MOD_H_

/*------------------------------------ Includes Start --------------------------------------*/
#include "MPU6050/MPU_Lcfg.h"
#include "cmsis_os.h"
/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/

#define MPU_TASK_1_PERIODICITY_ms			100
//#define MPU_TASK_2_PERIODICITY_ms			10

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


void MPU_Int_Task(void);
void MPU_Task(void *argument);

//void MPU_Task_1(void *argument);
//void MPU_Task_2(void *argument);

#endif /* MPU_MODULE_MPU_MOD_H_ */
