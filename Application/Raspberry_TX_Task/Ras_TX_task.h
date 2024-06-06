/*
 * Ras_TX_task.h
 *
 *  Created on: Apr 27, 2024
 *      Author: moham
 */

#ifndef RAS_TX_TASK_H_
#define RAS_TX_TASK_H_

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include <string.h>


void Ras_TX_task_init(osMessageQueueId_t* ras_tx_MsgQueue ,osSemaphoreId_t* uart_Semaphore, UART_HandleTypeDef *huart);

void Ras_UART_Callback();

void Ras_TX_Task(void *argument);

void Ras_TX_add_to_q(uint8_t* str);


#endif /* RAS_TX_TASK_H_ */
