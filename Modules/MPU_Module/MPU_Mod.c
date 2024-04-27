/*
 * MPU_Mod.c
 *
 *  Created on: Apr 22, 2024
 *      Author: Salem Elfaidy
 */

#include "MPU_Mod.h"



void TASK_MPU(void *PvMPUInitData)
{
	Task_MPU_Data *pMPU = (Task_MPU_Data *)PvMPUInitData;

	if(pMPU->MPUTaskState == TASK_MPU_REQUESTE_DATA)
	{
		if(pMPU->h_MPU->dataState == MPU_DATA_STATE_NOT_REQUESTED)
		{
			MPU_enuGetGyroAccelReadings_DMA(pMPU->h_MPU, pMPU->AccelGyroDataBuffer);
			//pMPU->MPUTaskState = TASK_MPU_DATA_REQUESTED;
		}

		if(pMPU->h_MPU->dataState == MPU_DATA_STATE_RECEIVED)
		{
			MPU_GetReadings(pMPU->h_MPU);
			pMPU->MPUTaskState = TASK_MPU_DATA_READY;
		}
	}
	else
	{
		/* For RTOS : */
		//pMPU->MPUTaskState = TASK_MPU_REQUESTE_DATA;
		//Sleep.

		/* For Timer_Sys : */
		// Do Nothing.
		// Change the task state to "TASK_MPU_REQUESTE_DATA" in the Sys_Timer, when u need to request data again.
	}

}

//TODO: in Timer_Sys, After buffering the MPU data in the buffer module, make pMPU->MPUTaskState = TASK_MPU_DONE;, Then The MPU task won't run again unless u changed to pMPU->MPUTaskState = TASK_MPU_REQUESTE_DATA; in teh Sys_Timer.
