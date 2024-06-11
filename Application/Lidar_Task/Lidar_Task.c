#include "Lidar_Task.h"
#include "../../Modules/Log_Module/log.h"

osSemaphoreId_t* Lidar_Semaphore;
Lidar_Handle *pLidar;



void Lidar_Init_Task(osSemaphoreId_t* lidar_sem,Lidar_Handle *Copy_hLidar,UART_HandleTypeDef *huartX)
{
	Lidar_Semaphore = lidar_sem;
	pLidar = Copy_hLidar;
	Lidar_voidInit(Copy_hLidar,huartX);

}


void Lidar_Task(void *argument)
{

	uint16_t count = 0;
	/* Get system tick frequency */
	uint32_t tickFrequency = osKernelGetTickFreq();

	/* Convert delay to ticks */
	uint32_t delayTicks = (Lidar_TASK_1_PERIODICITY_ms * tickFrequency) / 1000;

	/* Get the current Kernel tick and set next run time */
	uint32_t PeriodicityTick = osKernelGetTickCount() + delayTicks;


	for(;;)
	{
		/* Acquire semaphore to synchronize data request */
		osSemaphoreAcquire(*Lidar_Semaphore, osWaitForever);

		/* Request Lidar data */
		Lidar_voidReceiveData(pLidar);

		/* Wait for data to be ready, assuming ISR will release semaphore */
		osSemaphoreAcquire(*Lidar_Semaphore, osWaitForever);

		/* Get the data ready (calculations)*/
		Lidar_voidGetDistance(pLidar);

		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		static uint32_t count =0;
		//logs_debg("ras","{'times':'%d'}",count++);

		//TODO: send the data 
		logs_debg("Lidar","{'distance':'%d','i':'%d'}",pLidar->Distance, count++);
		
		/* Give the semaphore */
		osSemaphoreRelease(*Lidar_Semaphore);

		/* Wait (Block the task) until the next period ( Task periodicity ) */
		osDelayUntil(PeriodicityTick);

		/* Increment the tick count for the next period */
		PeriodicityTick += delayTicks;
	}


}



void Lidar_RxFrameCallBack(void)
{
    osSemaphoreRelease(*Lidar_Semaphore);
}
