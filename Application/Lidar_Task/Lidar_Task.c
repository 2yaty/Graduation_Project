#include "Lidar_Task.h"


osSemaphoreId_t Lidar_Semaphore;



void Lidar_Init_Task(void)
{
	Lidar_Semaphore = osSemaphoreNew(1U, 1U, NULL);
	if (Lidar_Semaphore == NULL)
	{
	    /* Semaphore object not created, handle failure */
		//osError("Failed to create semaphore");
		return;
	}
}


void Lidar_Task(void *argument)
{
	Lidar_Handle *pLidar = (Lidar_Handle *)argument;

	/* Get system tick frequency */
	uint32_t tickFrequency = osKernelGetTickFreq();

	/* Convert delay to ticks */
	uint32_t delayTicks = (Lidar_TASK_1_PERIODICITY_ms * tickFrequency) / 1000;

	/* Get the current Kernel tick and set next run time */
	uint32_t PeriodicityTick = osKernelGetTickCount() + delayTicks;


	for(;;)
	{
		/* Acquire semaphore to synchronize data request */
		osSemaphoreAcquire(Lidar_Semaphore, osWaitForever);

		/* Request Lidar data */
		Lidar_voidReceiveData(pLidar);

		/* Wait for data to be ready, assuming ISR will release semaphore */
		osSemaphoreAcquire(Lidar_Semaphore, osWaitForever);

		/* Get the data ready (calculations)*/
		Lidar_voidGetDistance(pLidar);

		//TODO: send the data 

		
		/* Give the semaphore */
		osSemaphoreRelease(Lidar_Semaphore);

		/* Wait (Block the task) until the next period ( Task periodicity ) */
		osDelayUntil(PeriodicityTick);

		/* Increment the tick count for the next period */
		PeriodicityTick += delayTicks;
	}


}


void Lidar_RxFrameCallBack(void)
{
    osSemaphoreRelease(Lidar_Semaphore);
}