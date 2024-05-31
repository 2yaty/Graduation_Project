/*
 * MPU_Mod.c
 *
 *  Created on: Apr 22, 2024
 *      Author: Salem Elfaidy
 */

#include <MPU_Task/MPU_Mod.h>



osMessageQueueId_t* mpu_Tx_MsgQueue;
osSemaphoreId_t* mpu_Semaphore;

void dataBuffering(float *data);


void MPU_Init_Task(osMessageQueueId_t* MPU_Tx_MsgQueue ,osSemaphoreId_t* MPU_Semaphore)
{
	//MPU_Semaphore = osSemaphoreNew(1U, 1U, NULL);
	if (MPU_Semaphore == NULL)
	{
	    /* Semaphore object not created, handle failure */
		//osError("Failed to create semaphore");
		return;
	}
	mpu_Tx_MsgQueue = MPU_Tx_MsgQueue;
	mpu_Semaphore = MPU_Semaphore;

}


void MPU_Task(void *argument)
{
	Task_MPU_Data *pMPU = (Task_MPU_Data *)argument;

	/* Get system tick frequency */
	uint32_t tickFrequency = osKernelGetTickFreq();

	/* Convert delay to ticks */
	uint32_t delayTicks = (MPU_TASK_PERIODICITY_ms * tickFrequency) / 1000;

	/* Get the current Kernel tick and set next run time */
	uint32_t PeriodicityTick = osKernelGetTickCount() + delayTicks;


	for(;;)
	{
		/* Acquire semaphore to synchronize data request */
		osSemaphoreAcquire(mpu_Semaphore, osWaitForever);

		/* Request accelerometer and gyroscope data */
		MPU_enuGetGyroAccelReadings_DMA(pMPU->h_MPU, pMPU->AccelGyroDataBuffer);

		/* Wait for data to be ready, assuming ISR will release semaphore */
		osSemaphoreAcquire(mpu_Semaphore, osWaitForever);

		/* Get the data ready (calculations)*/
		MPU_GetReadings(pMPU->h_MPU);

		/* Queue the data into Tx buffer */
		dataBuffering(pMPU->AccelGyroDataBuffer);

		/* Give the semaphore */
		osSemaphoreRelease(mpu_Semaphore);

		/* Wait (Block the task) until the next period ( Task periodicity ) */
		osDelayUntil(PeriodicityTick);

		/* Increment the tick count for the next period */
		PeriodicityTick += delayTicks;
	}


}


void MPU_RxFrameCallback(void)
{
	osSemaphoreRelease(mpu_Semaphore);
}


void dataBuffering(float *data)
{
    cJSON *root = cJSON_CreateObject();
    if(!root){return;} // Handle memory failure

    cJSON *AccelBranch = NULL;
    cJSON *GyroBranch = NULL;

    cJSON_AddStringToObject(root, "S", "MPU");
    cJSON_AddItemToObject(root, "G", AccelBranch = cJSON_CreateObject());
    cJSON_AddNumberToObject(AccelBranch, "X", data[0]);
    cJSON_AddNumberToObject(AccelBranch, "Y", data[1]);
    cJSON_AddNumberToObject(AccelBranch, "Z", data[2]);
    cJSON_AddItemToObject(root, "A", GyroBranch = cJSON_CreateObject());
    cJSON_AddNumberToObject(GyroBranch, "X", data[3]);
    cJSON_AddNumberToObject(GyroBranch, "Y", data[4]);
    cJSON_AddNumberToObject(GyroBranch, "Z", data[5]);

    uint8_t* msg = cJSON_PrintUnformatted(root);
    if (msg)
    {
        osMessageQueuePut(*mpu_Tx_MsgQueue, &msg, NULL, osWaitForever);
        free(msg);
    }

    cJSON_Delete(root);
}

