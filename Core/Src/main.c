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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/*************** Fully working Example of Queue ****************/
/*
#define MSGQUEUE_OBJECTS 16                     // number of Message Queue Objects

typedef struct {                                // object data type
  char *Buf;
  uint8_t Idx;
} MSGQUEUE_OBJ_t;

osMessageQueueId_t mid_MsgQueue;


osThreadId_t tid_Thread_MsgQueue1;              // thread id 1
osThreadId_t tid_Thread_MsgQueue2;              // thread id 2


void Thread_MsgQueue1 (void *argument);         // thread function 1
void Thread_MsgQueue2 (void *argument);         // thread function 2

int Init_MsgQueue (void) {

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
}

void Thread_MsgQueue1 (void *argument) {

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
    osMessageQueuePut(mid_MsgQueue, &msg, 0U, 0U);
    osThreadYield();                                            // suspend thread
  }
}

void Thread_MsgQueue2 (void *argument) {
//  MSGQUEUE_OBJ_t msg;
	char* msg;
  osStatus_t status;

  while (1) {
    ; // Insert thread code here...
    status = osMessageQueueGet(mid_MsgQueue, &msg, NULL, osWaitForever);   // wait for message
    status = osOK;
    if (status == osOK) {
      ; // process data
    }
  }
}
*/
#include "testing/test.h"
#include "MOV_Task/MOV.h"
#include "Lidar_Task/Lidar_Task.h"
#include "FCW_Application/FCW_App.h"
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
char n=0, i =0, j =0;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart6_tx;
DMA_HandleTypeDef hdma_usart6_rx;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "MPU",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myTask03 */
osThreadId_t myTask03Handle;
const osThreadAttr_t myTask03_attributes = {
  .name = "Ras_Tx",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Ras_Tx_Queue01 */
osMessageQueueId_t Ras_Tx_Queue01Handle;
const osMessageQueueAttr_t Ras_Tx_Queue01_attributes = {
  .name = "Ras_Tx_Queue01"
};
/* Definitions for MPU_Semaphore */
osSemaphoreId_t MPU_SemaphoreHandle;
const osSemaphoreAttr_t MPU_Semaphore_attributes = {
  .name = "MPU_Semaphore"
};
/* Definitions for Ras_Tx_Semaphore */
osSemaphoreId_t Ras_Tx_SemaphoreHandle;
const osSemaphoreAttr_t Ras_Tx_Semaphore_attributes = {
  .name = "Ras_Tx_Semaphore"
};
/* USER CODE BEGIN PV */
/* Definitions for Mov_Semaphore */
osSemaphoreId_t MOV_SemaphoreHandle;
const osSemaphoreAttr_t MOV_Semaphore_attributes = {
  .name = "MOV_Semaphore"
};

/* Definitions for Lidar_Semaphore */
osSemaphoreId_t Lidar_SemaphoreHandle;
const osSemaphoreAttr_t Lidar_Semaphore_attributes = {
  .name = "Lidar_Semaphore"
};
/* Definitions for myTask03 */
osThreadId_t myTask04Handle;
const osThreadAttr_t myTask04_attributes = {
  .name = "Mov",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

osThreadId_t myTask05Handle;
const osThreadAttr_t myTask05_attributes = {
  .name = "Lidar",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
Bluetooth_Handler hbluetooth1;

Task_MPU_Data data =
{
	.h_MPU = &hMPU,
};

Task_MOV_Data mov_Data=
{
		.hmotor_1 = &MOTOR_1_cfg,
		.hmotor_2 = &MOTOR_2_cfg,
		.h_bluetooth = &hbluetooth1
};

SYS_State_t state = STS_DO_NOTHING;

Lidar_Handle hluna;

FCW_Handle fcwHandle ;


//MOV_Handler hmove ;
//int n =0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);

/* USER CODE BEGIN PFP */
void Task1(void *argument);
void Task2(void *argument);
void Objects_init(void);
void Task_Test(void *argument);
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
//  Init_MsgQueue();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM3_Init();
  MX_USART6_UART_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
//  SystemClock_Cfg();
//  Peripherals_Init();


  MPU_enuInit(&hMPU);


//  HAL_TIM_Base_Start_IT(&htim2);
  Objects_init();

//  unsigned char data;
//  HAL_UART_Receive_IT(&huart6, &data, sizeof(uint8_t));

  //MOV_enuReceiveData(&hbluetooth1);

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of MPU_Semaphore */
  MPU_SemaphoreHandle = osSemaphoreNew(1, 1, &MPU_Semaphore_attributes);

  /* creation of Ras_Tx_Semaphore */
  Ras_Tx_SemaphoreHandle = osSemaphoreNew(1, 1, &Ras_Tx_Semaphore_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  MOV_SemaphoreHandle = osSemaphoreNew(1U, 0U, &MOV_Semaphore_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  Lidar_SemaphoreHandle = osSemaphoreNew(1U, 1U, &Lidar_Semaphore_attributes);

  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of Ras_Tx_Queue01 */
  Ras_Tx_Queue01Handle = osMessageQueueNew (10, 270, &Ras_Tx_Queue01_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
//  testing_logs_init(&Ras_Tx_Queue01Handle);
  Ras_TX_task_init(&Ras_Tx_Queue01Handle,&Ras_Tx_SemaphoreHandle,&huart2);
  MPU_Init_Task(&Ras_Tx_Queue01Handle,&MPU_SemaphoreHandle,&fcwHandle);
  MOV_Init_Task(&hbluetooth1,&MOV_SemaphoreHandle,&fcwHandle);
  Lidar_Init_Task(&Lidar_SemaphoreHandle,&hluna, &huart6,&fcwHandle);
//  Test1_init(&Ras_Tx_Queue01Handle);
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
  //printTaskState( "default Task",osThreadGetState(defaultTaskHandle),"[Before Kernel Start]");
  /* creation of myTask02 */

  /* creation of myTask03 */
  myTask03Handle = osThreadNew(Ras_TX_Task, NULL, &myTask03_attributes);
  //printTaskState( "Ras Task",osThreadGetState(myTask03Handle),"[Before Kernel Start]");
  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* creation of myTask04 */
  myTask04Handle = osThreadNew(MOV_Task, &mov_Data, &myTask04_attributes);
  //printTaskState( "Mov Task",osThreadGetState(myTask04Handle),"[Before Kernel Start]");
  /* creation of myTask05 */
  myTask05Handle = osThreadNew(Lidar_Task, NULL, &myTask05_attributes);
  //printTaskState( "Lidar Task",osThreadGetState(myTask05Handle),"[Before Kernel Start]");
  //myTask05Handle = osThreadNew(Task_Test, NULL, &myTask05_attributes);

  myTask02Handle = osThreadNew(MPU_Task, &data, &myTask02_attributes);
  //printTaskState( "MPU Task",osThreadGetState(myTask02Handle),"[Before Kernel Start]");

  //printing states before starting the kernel

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
//  Ras_TX_task_init(&Ras_Tx_Queue01Handle , &Ras_Tx_SemaphoreHandle, &huart2);
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();


  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 15;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.Pulse = 24;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 19200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
  /* DMA1_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
  /* DMA2_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 5, 1);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
  /* DMA2_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB1 PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


/**
 *** Callback Functions ********************************************************
 **/

/* ----------------------------- USART -------------------------------- */

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

	if(huart->Instance == USART2)
		{
			Ras_UART_Callback();

		}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		/* RSPB_RxCpltProcess(huart); */
		//Lidar_RxFrameCallBack();
//		logs_debg("Ldr RXCP", "in the cp");
		BLUTH_RxCpltProcess(&hbluetooth1);
	}
	else if(huart->Instance == USART2)
	{
//		Ras_UART_Callback();
		//osSemaphoreRelease(Ras_Tx_SemaphoreHandle);
//		testing_UART_task4_CallBack();
	}
	else if(huart->Instance == USART6)
	{
		//BLUTH_RxCpltProcess(&hbluetooth1);
		Lidar_RxFrameCallBack();
	}
}

/* ----------------------------- I2C -------------------------------- */

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c->Instance == I2C1)
	{
		MPU_RxCpltProcess(&hMPU);
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
	  hbluetooth1.huartX = &huart1;
//	  hmove.SourceBuffer = hbluetooth1.ReceivingQueue;
//	  hmove.hmotor_1 = &MOTOR_1_cfg;
//	  hmove.hmotor_2 = &MOTOR_2_cfg;
}



void Task_Test(void *argument)
{

	char *msg = "Mostafa Ali Known as 3eed";
	uint8_t i = 0;
	for(;;)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		static uint32_t count =0;
		logs_debg("ras","{'times':'%d'}",count++);
		vTaskDelay(400);
	}
}


void Task1(void *argument)
{

	char *msg = "Mostafa Ali Known as 3eed";
	uint8_t i = 0;
	for(;;)
	{
		 char c = msg[i++];
		 if (i >= 25){
			 i = 0;
		 }
		 c = 'h';
		 vTaskDelay(5);
	}
}


void Task2(void *argument)
{
	char *msg = "Mostafa Ali Known as 3eed";
		uint8_t i = 0;
		for(;;)
		{
			 char c = msg[i++];
			 if (i >= 25){
				 i = 0;
			 }
			 c = 'h';
			 vTaskDelay(5);
		}
}


/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
//	  printTaskState( "default Task",osThreadGetState(defaultTaskHandle),"[From Default Task]");
//	  printTaskState( "MPU Task",osThreadGetState(myTask02Handle),"[From Default Task]");
//	  printTaskState( "Ras Task",osThreadGetState(myTask03Handle),"[From Default Task]");
//	  printTaskState( "Mov Task",osThreadGetState(myTask04Handle),"[From Default Task]");
//	  printTaskState( "Lidar Task",osThreadGetState(myTask05Handle),"[From Default Task]");
      osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  float32_t data[6] = {1, -1, 1.5, 2, 3, 4};

  /* Infinite loop */
  for(;;)
  {
	  cJSON *root = cJSON_CreateObject();
	  if(!root){return;} // Handle memory failure
	  n++;
	  cJSON *AccelBranch = NULL;
	  cJSON *GyroBranch = NULL;
	  cJSON_AddStringToObject(root, "S", "MPU");
	  cJSON_AddItemToObject(root, "G", AccelBranch = cJSON_CreateObject());
	  cJSON_AddNumberToObject(AccelBranch, "X", data[0] +1);
	  cJSON_AddNumberToObject(AccelBranch, "Y", data[1] +1);
	  cJSON_AddNumberToObject(AccelBranch, "Z", data[2] +1);
	  cJSON_AddItemToObject(root, "A", GyroBranch = cJSON_CreateObject());
	  cJSON_AddNumberToObject(GyroBranch, "X", data[3] +1);
	  cJSON_AddNumberToObject(GyroBranch, "Y", data[4] +1);
	  cJSON_AddNumberToObject(GyroBranch, "Z", data[5] +1);

	  uint8_t* msg = cJSON_PrintUnformatted(root);
	  cJSON_Delete(root);
	  uint8_t size = strlen(msg);

	  if (msg)
	  {
		  osMessageQueuePut(Ras_Tx_Queue01Handle, msg, NULL, osWaitForever);
		  free(msg);
	  }

    osDelay(5);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
	char msg[100];
  /* Infinite loop */
  for(;;)
  {

	uint32_t num = osMessageQueueGetCount (Ras_Tx_Queue01Handle);
	i++;
	if(osOK == osMessageQueueGet(Ras_Tx_Queue01Handle, &msg, NULL, osWaitForever )){

//		osSemaphoreAcquire(Ras_Tx_SemaphoreHandle,osWaitForever);
//		HAL_UART_Transmit_IT(&huart2, (uint8_t*)"Salem", strlen("Salem"));
		j++;
	}
	else if(osErrorResource == osMessageQueueGet(Ras_Tx_Queue01Handle, msg, NULL, osWaitForever )){;}
	else if(osErrorParameter == osMessageQueueGet(Ras_Tx_Queue01Handle, msg, NULL, osWaitForever )){;}
	else if(osErrorTimeout == osMessageQueueGet(Ras_Tx_Queue01Handle, msg, NULL, osWaitForever )){;}


	osDelay(7);
    //osDelay(7);
  }
  /* USER CODE END StartTask03 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM2) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
