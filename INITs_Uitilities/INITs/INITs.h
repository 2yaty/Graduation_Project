/********************************************************************************
 * @file           : MPU.h														*
 * @author         : Salem&Omar  15/12/2023	 												*
 * @brief          : Contains  APIs to control MPU sensor.          			*
 *******************************************************************************/


#ifndef INITS_INITS_H_
#define INITS_INITS_H_

#include "stm32f4xx_hal.h"


extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

extern UART_HandleTypeDef huart6;
extern DMA_HandleTypeDef hdma_usart6_tx;
extern DMA_HandleTypeDef hdma_usart6_rx;

extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;

extern I2C_HandleTypeDef hi2c1;
extern DMA_HandleTypeDef hdma_i2c1_rx;

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;


void SystemClock_Cfg(void);
void Peripherals_Init(void);

/*------------------------- Software Interfaces Declarations End ----------------------------*/


#endif /* INITS_INITS_H_ */
