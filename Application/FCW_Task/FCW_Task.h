#ifndef FCW_TASK_H
#define FCW_TASK_H

/*------------------------------------ Includes Start --------------------------------------*/
#include "../H_Drivers/../FCW_Application/FCW_App.h"
#include "cmsis_os.h"
/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/

#define FCW_TASK_1_PERIODICITY_ms			100

/*-------------------------- Macro• Functions Declarations Start ---------------------------*/

/*-------------------------- Macro• Functions Declarations End -----------------------------*/

/*------------------------------ Data type Declarations Start ------------------------------*/



/*------------------------------ Data type Declarations End --------------------------------*/


/*------------------------- Software Interfaces Declarations Start --------------------------*/


void FCW_Init_Task(void);
void FCW_Task(void *argument);


#endif 