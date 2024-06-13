//#include "FCW_Task.h"
//
//enum_FC_Warnings_t Warning_Status ;
//osSemaphoreId_t* FCW_Semaphore;
//
//
//
//
//void FCW_Task_Init(osSemaphoreId_t* fcw_sem)
//{
//	FCW_Semaphore = fcw_sem;
//}
//
//
//
//void FCW_Task(void *argument)
//{
//	FCW_Handle *pFCW = (FCW_Handle *)argument;
//
//	/* Get system tick frequency */
//	uint32_t tickFrequency = osKernelGetTickFreq();
//
//	/* Convert delay to ticks */
//	uint32_t delayTicks = (FCW_TASK_1_PERIODICITY_ms * tickFrequency) / 1000;
//
//	/* Get the current Kernel tick and set next run time */
//	uint32_t PeriodicityTick = osKernelGetTickCount() + delayTicks;
//
//
//	for(;;)
//	{
//		/* Acquire semaphore to synchronize data request */
//		//osSemaphoreAcquire(FCW_Semaphore, osWaitForever);
//
//		/* Request FCW Module calculated time */
//		pFCW->CalculatedTime = FCW_u8TimeToCollision(pFCW->Speed , pFCW->Distance , pFCW->AccX);
//		/* Wait for data to be ready, assuming ISR will release semaphore */
//		//osSemaphoreAcquire(FCW_Semaphore, osWaitForever);
//
//		/* Get the warning status according to the calculated time */
//		Warning_Status = FCW_enuIsWarning(pFCW->CalculatedTime);
//		/* Give the semaphore */
//		//osSemaphoreRelease(Lidar_Semaphore);
//
//		/* Wait (Block the task) until the next period ( Task periodicity ) */
//		//osDelayUntil(PeriodicityTick);
//
//		/* Increment the tick count for the next period */
//		//PeriodicityTick += delayTicks;
//	}
//
//
//}
//
//
//
