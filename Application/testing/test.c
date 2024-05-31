/*
 * test.c
 *
 *  Created on: Apr 30, 2024
 *      Author: Salem Elfaidy
 */
#include "test.h"


osMessageQueueId_t* mid_MsgQ_1;

osMessageQueueId_t* mid_MsgQ_3;
osSemaphoreId_t* 	uart_sem_3;
UART_HandleTypeDef* uart_handle_3;



void log_send_func(int8_t* str){
	osMessageQueuePut(*mid_MsgQ_1, &str,  0U, 0U);

}
void testing_logs_init(osMessageQueueId_t* mid_MsgQueue){

	mid_MsgQ_1 = mid_MsgQueue;
	logs_init(log_send_func);
}

void testing_logs_task1(void* args){
	uint8_t i = 0;

	for(;;){

		logs_debg("task1", "ya rab teshatghal %d",i++);
		if(i==6) i=0;
		osDelay(5);
	}


}
void testing_logs_task2(void* args){
	char* msg;
	uint8_t i = 0;

	for(;;){

		if(osOK == osMessageQueueGet(*mid_MsgQ_1, &msg, NULL, osWaitForever )){

				i++;
			}
	}

}




void testing_UART_init(osMessageQueueId_t* mid_MsgQueue , osSemaphoreId_t* uart_sem , UART_HandleTypeDef* uart_handle){

	mid_MsgQ_3 = mid_MsgQueue;
	uart_sem_3 = uart_sem;
	uart_handle_3 = uart_handle;
}


void testing_UART_task3(void* args){
	char msgs[][10] = {"3eed" , "ayoub" , "balio", "khairy" ,"abo ali"};
		uint8_t i  = 0;
	//  MSGQUEUE_OBJ_t msg;
		char* msg;
	  while (1) {
	    ; // Insert thread code here...
	    msg = msgs[i++];

	    if(i > 4) i = 0;
	    osMessageQueuePut(*mid_MsgQ_3, msg, 0U, 0U);
	    osDelay(5);                                           // suspend thread
	  }
}
void testing_UART_task4(void* args){

	char msg[10];
  osStatus_t status;
  uint8_t i ;

  while (1) {
     // Insert thread code here...
	  i = osMessageQueueGetCount(*mid_MsgQ_3);
    status = osMessageQueueGet(*mid_MsgQ_3, &msg, NULL, osWaitForever);   // wait for message
    if (status == osOK) {
       // process data
    	osSemaphoreAcquire(*uart_sem_3,osWaitForever);
		HAL_UART_Transmit_IT(uart_handle_3, msg, strlen(msg));
    }

    	osDelay(15);
  }
}
void testing_UART_task4_CallBack(void){
	osSemaphoreRelease(*uart_sem_3);
}











