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

void Ras_TX_task_init(osMessageQueueId_t* ras_tx_MsgQueue ,osSemaphoreId_t* uart_Semaphore, UART_HandleTypeDef *huart){
	ras_tx_MsgQueue = ras_tx_MsgQueue;
	ras_huart = huart;
	ras_Semaphore = uart_Semaphore;
}



void Ras_TX_Task(void *argument){

	cJSON* msg;

	//osStatus_t status;
	for(;;)
	  {

		while(osOK==osMessageQueueGet(*ras_tx_MsgQueue, msg, NULL, osWaitForever )){

			osSemaphoreAcquire(*ras_Semaphore,osWaitForever);
			HAL_UART_Transmit_DMA(ras_huart , cJSON_Print(msg),strlen(cJSON_Print(msg)));

		}


		vTaskDelay(RAS_TX_TASK_PERIODICITY);
	  }
}


void Ras_UART_Callback(){
	osSemaphoreRelease(*ras_Semaphore);
}
