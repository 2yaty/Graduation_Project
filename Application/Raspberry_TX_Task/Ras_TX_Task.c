/*
 * Ras_TX_Task.c
 *
 *  Created on: Apr 27, 2024
 *      Author: moham
 */


#include "Ras_TX_task.h"

osMessageQueueId_t* ras_tx_MsgQueue ;
UART_HandleTypeDef* ras_huart;
osSemaphoreId_t* ras_Semaphore;

void Ras_TX_task_init(osMessageQueueId_t* ras_Tx_MsgQueue ,osSemaphoreId_t* uart_Semaphore, UART_HandleTypeDef *huart){
	ras_tx_MsgQueue = ras_Tx_MsgQueue;
	ras_huart = huart;
	ras_Semaphore = uart_Semaphore;
}



void Ras_TX_Task(void *argument){

	void* msg = NULL;

	//osStatus_t status;
	for(;;)
	  {

		uint32_t num = osMessageQueueGetCount (*ras_tx_MsgQueue);

		if(osOK == osMessageQueueGet(*ras_tx_MsgQueue, &msg, NULL, osWaitForever )){

			osSemaphoreAcquire(*ras_Semaphore,osWaitForever);
			HAL_UART_Transmit_DMA(ras_huart, (uint8_t*)"Salem", strlen("Salem"));

		}
		else if(osErrorResource == osMessageQueueGet(*ras_tx_MsgQueue, msg, NULL, osWaitForever )){;}
		else if(osErrorParameter == osMessageQueueGet(*ras_tx_MsgQueue, msg, NULL, osWaitForever )){;}
		else if(osErrorTimeout == osMessageQueueGet(*ras_tx_MsgQueue, msg, NULL, osWaitForever )){;}


		osDelay(RAS_TX_TASK_PERIODICITY);
	  }
}


void Ras_UART_Callback(){
	osSemaphoreRelease(*ras_Semaphore);
}
