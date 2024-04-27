/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum
{
	SYS_BLUETOOTH_RX,
	SYS_MPU_ACTION,
	SYS_MPU_DATA_BUFFER,
	SYS_MOVEMENT_ACTION,
	SYS_FRAME_COMPLETE,
	STS_DO_NOTHING

}SYS_State_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
Task_MPU_Data data =
{
	.h_MPU = &hMPU,
	.MPUTaskState = TASK_MPU_REQUESTE_DATA
};

SYS_State_t state = STS_DO_NOTHING;


Bluetooth_Handler hbluetooth1;
MOV_Handler hmove ;
//int n =0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */
void Objects_init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  /* USER CODE BEGIN 2 */
  SystemClock_Cfg();
  Peripherals_Init();

  MPU_enuInit(&hMPU);
//  MOV_voidSetComm(&hbluetooth1);
//  MOV_voidInitMovement();
//  HAL_TIM_Base_Start_IT(&htim2);
//  Objects_init();

//  unsigned char data;
//  HAL_UART_Receive_IT(&huart6, &data, sizeof(uint8_t));

  //MOV_enuReceiveData(&hbluetooth1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(state == SYS_MPU_ACTION)
	  {
		  TASK_MPU(&data);
		  state = STS_DO_NOTHING;
	  }
	  else if(state == SYS_MPU_DATA_BUFFER)
	  {
		  // buffering process.
          state = STS_DO_NOTHING;
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}



/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
	{
		static uint8_t Loc_su8Count =0;
		Loc_su8Count++;

		if((Loc_su8Count % 5 == 0) && (Loc_su8Count <= 100)) //every 10 ms
		{
			if(data.MPUTaskState == TASK_MPU_REQUESTE_DATA)
			{
				state = SYS_MPU_ACTION;
			}
			else if(data.MPUTaskState == TASK_MPU_DATA_READY)
			{
				data.MPUTaskState = TASK_MPU_DONE;
				state = SYS_MPU_DATA_BUFFER;
			}
		}

		if(Loc_su8Count == 100)
		{
			data.MPUTaskState = TASK_MPU_REQUESTE_DATA;
			Loc_su8Count =0;
		}


//		switch (state) {
//			case SYS_FRAME_COMPLETE:
//				MOV_enuFrameBuffering(&hbluetooth1);
//				state = SYS_MOVEMENT_ACTION;
//				break;
//			case SYS_MOVEMENT_ACTION:
//				if(Loc_su8Count == 60)
//				{
//					if(MOV_enuMovementHandler(&hmove) == E_PROCESS_COMPLETE)
//					{/* Do nothing */}
//					Loc_su8Count =0;
//				}
//				break;
//			default:
//				break;
//		}

	}


}


void MOV_voidRxFrameCallback(void)
{
	state = SYS_FRAME_COMPLETE;

}



/**
 *** Callback Functions ********************************************************
 **/

/* ----------------------------- USART -------------------------------- */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		/* RSPB_RxCpltProcess(huart); */
	}
	else if(huart->Instance == USART2)
	{
		/* LUNA_RxCpltProcess(huart); */
	}
	else if(huart->Instance == USART6)
	{
		BLUTH_RxCpltProcess(&hbluetooth1);
	}
}

/* ----------------------------- I2C -------------------------------- */

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c->Instance == I2C1)
	{
		/* RSPB_RxCpltProcess(huart); */
	}
	else if(hi2c->Instance == I2C2)
	{

	}
	else if(hi2c->Instance == I2C3)
	{

	}

}


void Objects_init(void)
{
	  hbluetooth1.huartX = &huart6;
	  hmove.SourceBuffer = hbluetooth1.ReceivingQueue;
	  hmove.hmotor_1 = &MOTOR_1_cfg;
	  hmove.hmotor_2 = &MOTOR_2_cfg;
}




/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
