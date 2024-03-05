/*
 * Queue.h
 *
 *  Created on: Feb 24, 2024
 *      Author: Salem Elfaidy
 */

#ifndef MOVEMENT_QUEUE_H_
#define MOVEMENT_QUEUE_H_

/*------------------------------------ Includes Start --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

/*------------------------------------ Includes End ----------------------------------------*/

/*-------------------------- Macro• Functions Declarations Start ---------------------------*/

/*-------------------------- Macro• Functions Declarations End -----------------------------*/

/*------------------------------ Data type Declarations Start ------------------------------*/
// A linked list (LL) node to store a queue entry
struct QNode {
	unsigned char key;
	struct QNode* next;
};

// The queue, front stores the front node of LL and rear
// stores the last node of LL
typedef struct Queue {
	struct QNode *front, *rear;
}Queue_t;

/*------------------------------ Data type Declarations End --------------------------------*/


/*------------------------- Software Interfaces Declarations Start --------------------------*/

struct Queue* createQueue();
void enQueue(struct Queue* q, unsigned char k);
signed char deQueue(struct Queue* q, unsigned char *K);


#endif /* MOVEMENT_QUEUE_H_ */
