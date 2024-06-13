

#ifndef LIDAR_TASK_H
#define LIDAR_TASK_H

/*------------------------------------ Includes Start --------------------------------------*/
#include "TF_Lidar/Lidar.h"
#include "FCW_Application/FCW_App.h"
#include "cmsis_os.h"
/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/

#define Lidar_TASK_1_PERIODICITY_ms			71

/*-------------------------- Macro• Functions Declarations Start ---------------------------*/

/*-------------------------- Macro• Functions Declarations End -----------------------------*/

/*------------------------------ Data type Declarations Start ------------------------------*/
//typedef struct
//{
//	uint8_t Speed        ;
//	float AccX           ;
//	float Distance       ;
//}FCW_Handle;


/*------------------------------ Data type Declarations End --------------------------------*/


/*------------------------- Software Interfaces Declarations Start --------------------------*/


void Lidar_Init_Task(osSemaphoreId_t* lidar_sem,Lidar_Handle *Copy_hLidar,UART_HandleTypeDef *huartX , FCW_Handle* fcw);
void Lidar_Task(void *argument);
void Lidar_RxFrameCallBack(void);


#endif 
