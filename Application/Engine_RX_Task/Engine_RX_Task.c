/*
 * Ras_TX_Task.c
 *
 *  Created on: Apr 27, 2024
 *      Author: moham
 */


#include "Engine_RX_Task.h"


UART_HandleTypeDef* engine_huart;
osSemaphoreId_t* engine_Semaphore;
FCW_Handle* fcwPtr;

void Engine_RX_Task_init(osSemaphoreId_t* uart_Semaphore, UART_HandleTypeDef *huart, FCW_Handle* fcwptr){
	engine_huart = huart;
	engine_Semaphore = uart_Semaphore;
	fcwPtr = fcwptr;
}



void Engine_RX_Task(void *argument){

	uint8_t rec_data[2];

	for(;;)
	  {

	    HAL_UART_Receive_DMA(engine_huart,rec_data , sizeof(rec_data));

	    osSemaphoreAcquire(*engine_Semaphore,osWaitForever);

	    if (rec_data[0] == '0'){
	    	logs("speed","%d",rec_data[1]);
	    	fcwPtr->Speed = rec_data[1];
	    }
	    else if (rec_data[0] == '1'){

	    	if (rec_data[1] == 's'){
	    		logs("engine","start");
	    	}
	    	else if(rec_data[1] == 'e'){
	    		logs("engine","end");
	    	}
	    }

	  }
}


void Engine_Callback(){
	osSemaphoreRelease(*engine_Semaphore);
}


