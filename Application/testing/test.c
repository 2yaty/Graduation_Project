/*
 * test.c
 *
 *  Created on: Apr 30, 2024
 *      Author: Salem Elfaidy
 */
#include "test.h"


#if TEST1
/**
 * @Test Title: Logging Testing
 *
 * @Description: Testing the Log module using only  the log module and a messageQueue.
 *
 * @Concerns:
 *          testing if the log module is working properly with the freeRTOS
 *          because we didn't know whether it uses Heap or not.
 *
 * @Test Results:
 *          Test is succeeded. it needs more memory allocated for each task for the queue to use.
 *          The test succeeded on stack_size = 300 * 4.
 **/


osMessageQueueId_t* task1_msgQ;




void log_send_func(int8_t* str){
	uint8_t length = strlen(str);
	Test1_Data d ;
	strcpy(d.data,str);
	osMessageQueuePut(*task1_msgQ, &d,  0U, 0U);

}
void Test1_init(osMessageQueueId_t* mid_MsgQueue){

	task1_msgQ = mid_MsgQueue;
	logs_init(log_send_func);
}

void Test1_task1(void* args){
	uint8_t i = 0;

	for(;;){

		logs_debg("task1", "yarab teshtaghal %d",i++);
		if(i==6) i=0;
		osDelay(5);
	}


}
void Test1_task2(void* args){
	char* msg;
	uint8_t j = 0;
	Test1_Data d2;

	for(;;){

		if(osOK == osMessageQueueGet(*task1_msgQ, &d2, NULL, osWaitForever )){

				j = strlen(d2.data);
			}
		osThreadYield();
	}

}

#endif


#if TEST2
/**
 * @Test Title: Semaphores Testing
 *
 * @Description: Testing semaphores with UART and messageQueue.
 *
 * @Concerns:
 *          testing the UART with semaphore as a resource handler.
 *
 * @Test Results:
 *           Working perfectly.
 **/

osMessageQueueId_t* task2_msgQ;
osSemaphoreId_t* 	task2_uart_sem;
UART_HandleTypeDef* task2_uart_handle;



void Test2_init(osMessageQueueId_t* mid_MsgQueue , osSemaphoreId_t* uart_sem , UART_HandleTypeDef* uart_handle){

	task2_msgQ = mid_MsgQueue;
	task2_uart_sem = uart_sem;
	task2_uart_handle = uart_handle;
}


void Test2_task1(void* args){
	char msgs[][10] = {"3eed" , "ayoub" , "balio", "khairy" ,"abo ali"};
		uint8_t i  = 0;
	//  MSGQUEUE_OBJ_t msg;
		char* msg;
		uint8_t count ;
	  while (1) {
	    ; // Insert thread code here...
	    msg = msgs[i++];
	    count = osMessageQueueGetCount(*task2_msgQ);
	    if(i > 4) i = 0;
	    osMessageQueuePut(*task2_msgQ, &msg, 0U, 0U);
	    osDelay(5);                                           // suspend thread
	  }
}
void Test2_task2(void* args){

	char* msg;
  osStatus_t status;
  uint8_t count ;

  while (1) {
     // Insert thread code here...
	  count = osMessageQueueGetCount(*task2_msgQ);
    status = osMessageQueueGet(*task2_msgQ, &msg, NULL, osWaitForever);   // wait for message
    if (status == osOK) {
       // process data
    	osSemaphoreAcquire(*task2_uart_sem,osWaitForever);
//    	i = strlen(msg);
    	HAL_UART_Transmit_DMA(task2_uart_handle, msg, strlen(msg));
    }

    	osDelay(5);
  }
}
void Test2_UART_CallBack(void){
	osSemaphoreRelease(*task2_uart_sem);
}

#endif


#if TEST3
/**
 * @Test Title: Queue Testing
 *
 * @Description: Testing only the Queue.
 *
 * @Concerns:
 *          testing the Queue only due to doubting our understanding of the freeRTOS syntax.
 *
 * @Test Results:
 *
 *
 *
 **/

#define MSGQUEUE_OBJECTS 16                     // number of Message Queue Objects


osMessageQueueId_t* task3_msgQ;


//osThreadId_t tid_Thread_MsgQueue1;              // thread id 1
//osThreadId_t tid_Thread_MsgQueue2;              // thread id 2


//void Thread_MsgQueue1 (void *argument);         // thread function 1
//void Thread_MsgQueue2 (void *argument);         // thread function 2

void Test3_init (osMessageQueueId_t* ptr_MsgQueue) {
/*
  mid_MsgQueue = osMessageQueueNew(MSGQUEUE_OBJECTS, sizeof(MSGQUEUE_OBJ_t), NULL);
  if (mid_MsgQueue == NULL) {
    ; // Message Queue object not created, handle failure
  }

  tid_Thread_MsgQueue1 = osThreadNew(Thread_MsgQueue1, NULL, NULL);
  if (tid_Thread_MsgQueue1 == NULL) {
    return(-1);
  }
  tid_Thread_MsgQueue2 = osThreadNew(Thread_MsgQueue2, NULL, NULL);
  if (tid_Thread_MsgQueue2 == NULL) {
    return(-1);
  }

  return(0);
  */
	task3_msgQ = ptr_MsgQueue;
}

void Test3_task1 (void *argument) {

	char msgs[][10] = {"3eed" , "ayoub" , "balio", "khairy" ,"abo ali"};
	uint8_t i  = 0;
//  MSGQUEUE_OBJ_t msg;
	char* msg;
  while (1) {
    ; // Insert thread code here...
    msg = msgs[i++];
//    msg.Buf = msgs[i];                                        // do some work...
//    msg.Idx    = i++;
    if(i > 4) i = 0;
    osMessageQueuePut(*task3_msgQ, &msg, 0U, 0U);
    osThreadYield();                                            // suspend thread
  }
}

void Test3_task2 (void *argument) {
//  MSGQUEUE_OBJ_t msg;
	char* msg;
  osStatus_t status;
  uint8_t size ;

  while (1) {
    ; // Insert thread code here...
    size = osMessageQueueGetCount(*task3_msgQ);
    status = osMessageQueueGet(*task3_msgQ, &msg, NULL, osWaitForever);   // wait for message
    status = osOK;
    if (status == osOK) {
      ; // process data
    }
  }
}

#endif





