

#ifndef LIDAR_TASK_H
#define LIDAR_TASK_H

/*------------------------------------ Includes Start --------------------------------------*/
#include "TF_Lidar/Lidar.h"
#include "cmsis_os.h"
/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/

#define Lidar_TASK_1_PERIODICITY_ms			100

/*-------------------------- Macro• Functions Declarations Start ---------------------------*/

/*-------------------------- Macro• Functions Declarations End -----------------------------*/

/*------------------------------ Data type Declarations Start ------------------------------*/



/*------------------------------ Data type Declarations End --------------------------------*/


/*------------------------- Software Interfaces Declarations Start --------------------------*/


void Lidar_Init_Task(void);
void Lidar_Task(void *argument);


#endif 