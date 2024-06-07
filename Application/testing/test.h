/*
 * test.h
 *
 *  Created on: Apr 30, 2024
 *      Author: Salem Elfaidy
 */

#ifndef TESTING_TEST_H_
#define TESTING_TEST_H_
#include "cmsis_os.h"
#include "Log_Module/log.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>

#define TEST1	0
#define TEST2	0
#define TEST3	0
#define TEST4	1



//Failed: due to Hard Fault Error because the log module is using Heap memory in the arg lib.
typedef struct{
	char data[80];
}Test1_Data;

void Test1_init(osMessageQueueId_t* mid_MsgQueue);
void Test1_task1(void* args);
void Test1_task2(void* args);

void Test2_init(osMessageQueueId_t* mid_MsgQueue , osSemaphoreId_t* uart_sem , UART_HandleTypeDef* uart_handle);
void Test2_task1(void* args);
void Test2_task2(void* args);
void Test2_UART_CallBack(void);


void Test3_init (osMessageQueueId_t* ptr_MsgQueue);
void Test3_task1 (void *argument);
void Test3_task2 (void *argument);


void Test4_task(void *arg);

#endif /* TESTING_TEST_H_ */
