/*
 * MPU_Mod.c
 *
 *  Created on: Apr 22, 2024
 *      Author: Salem Elfaidy
 */

#include "MPU_Mod.h"


osSemaphoreId_t MPU_Semaphore;



void MPU_Int_Task(void)
{
	MPU_Semaphore = osSemaphoreNew(1U, 1U, NULL);
	if (MPU_Semaphore == NULL)
	{
	    /* Semaphore object not created, handle failure */
		//osError("Failed to create semaphore");
		return;
	}

}


void MPU_Task(void *argument)
{
	Task_MPU_Data *pMPU = (Task_MPU_Data *)argument;

	/* Get system tick frequency */
	uint32_t tickFrequency = osKernelGetTickFreq();

	/* Convert delay to ticks */
	uint32_t delayTicks = (MPU_TASK_1_PERIODICITY_ms * tickFrequency) / 1000;

	/* Get the current Kernel tick and set next run time */
	uint32_t PeriodicityTick = osKernelGetTickCount() + delayTicks;


	for(;;)
	{
		/* Acquire semaphore to synchronize data request */
		osSemaphoreAcquire(MPU_Semaphore, osWaitForever);

		/* Request accelerometer and gyroscope data */
		MPU_enuGetGyroAccelReadings_DMA(pMPU->h_MPU, pMPU->AccelGyroDataBuffer);

		/* Wait for data to be ready, assuming ISR will release semaphore */
		osSemaphoreAcquire(MPU_Semaphore, osWaitForever);

		/* Get the data ready (calculations)*/
		MPU_GetReadings(pMPU->h_MPU);

		/* Give the semaphore */
		osSemaphoreRelease(MPU_Semaphore);

		/* Wait (Block the task) until the next period ( Task periodicity ) */
		osDelayUntil(PeriodicityTick);

		/* Increment the tick count for the next period */
		PeriodicityTick += delayTicks;
	}


}


void MPU_RxFrameCallback(void)
{
	osSemaphoreRelease(MPU_Semaphore);
}



//void MPU_Task_1(void *argument)
//{
//	Task_MPU_Data *pMPU = (Task_MPU_Data *)argument;
//
//	/* Get system tick frequency */
//	uint32_t tickFrequency = osKernelGetTickFreq();
//
//	/* Convert delay to ticks */
//	uint32_t delayTicks = (MPU_TASK_1_PERIODICITY_ms * tickFrequency) / 1000;
//
//	/* Get the current Kernel tick */
//	uint32_t currentTick = osKernelGetTickCount();
//
//	/* Capture the semaphore from to MPU_Task_2 */
//	osSemaphoreAcquire(MPU_Semaphore, 0);
//
//	for(;;)
//	{
//		/* Set next run time */
//		delayTicks += currentTick;
//
//		/* Request the data */
//		MPU_enuGetGyroAccelReadings_DMA(pMPU->h_MPU, pMPU->AccelGyroDataBuffer);
//
//		/* Wait (Block the task) until the next period ( Task periodicity ) */
//		osDelayUntil(delayTicks);
//	}
//
//}
//
//
//void MPU_Task_2(void *argument)
//{
//	Task_MPU_Data *pMPU = (Task_MPU_Data *)argument;
//
//	for(;;)
//	{
//		/* Avoid case that task 2 takes the semaphore before task 1 */
//
//		/* Take the semaphore to wait the task until data be ready */
//		osSemaphoreAcquire(MPU_Semaphore, osWaitForever);
//
//		/* Get the data ready (calculations)*/
//		MPU_GetReadings(pMPU->h_MPU);
//
//		/* Give the semaphore for MPU_Task_2 */
//		osSemaphoreRelease(MPU_Semaphore);
//
//		/* Wait (Block the task) for a specific time */
//		osDelay(MPU_TASK_1_PERIODICITY_ms);
//	}
//
//}
