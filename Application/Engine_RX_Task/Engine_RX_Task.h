/*
 * Engine_RX_Task.h
 *
 *  Created on: Apr 27, 2024
 *      Author: moham
 */

#ifndef ENGINE_RX_TASK_H_
#define ENGINE_RX_TASK_H_

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include "../../Modules/Log_Module/log.h"
#include "FCW_Application/FCW_App.h"


void Engine_RX_Task_init(osSemaphoreId_t* uart_Semaphore, UART_HandleTypeDef *huart, FCW_Handle* fcwptr);

void Engine_Callback();

void Engine_RX_Task(void *argument);

//void Ras_TX_add_to_q(uint8_t* str);


#endif /* Engine_RX_Task_H_ */
