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


//Failed: due to Hard Fault Error because the log module is using Heap memory in the arg lib.
void testing_logs_init(osMessageQueueId_t* mid_MsgQueue);
void testing_logs_task1(void* args);
void testing_logs_task2(void* args);

void testing_UART_init(osMessageQueueId_t* mid_MsgQueue , osSemaphoreId_t* uart_sem , UART_HandleTypeDef* uart_handle);
void testing_UART_task3(void* args);
void testing_UART_task4(void* args);
void testing_UART_task4_CallBack(void);




#endif /* TESTING_TEST_H_ */
