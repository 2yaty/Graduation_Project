/********************************************************************************
 * @file           : Queue.c													*
 * @author         : Salem Elfaidy												*
 * @brief          : Contains the static code to implement a queue.				*
 *******************************************************************************/

#include "Queue.h"


// A utility function to create a new linked list node.
struct QNode* newNode(unsigned char k)
{
	struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
	temp->key = k;
	temp->next = NULL;
	return temp;
}

// A utility function to create an empty queue
struct Queue* createQueue()
{
	struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
	q->front = q->rear = NULL;
	return q;
}

// The function to add a key k to q
void enQueue(struct Queue* q, unsigned char k)
{
	// Create a new LL node
	struct QNode* temp = newNode(k);

	// If queue is empty, then new node is front and rear
	// both
	if (q->rear == NULL) {
		q->front = q->rear = temp;
		return;
	}

	// Add the new node at the end of queue and change rear
	q->rear->next = temp;
	q->rear = temp;
}

// Function to remove a key from given queue q
signed char deQueue(struct Queue* q, unsigned char *K)
{
	// If queue is empty, return NULL.
	if (q->front == NULL)
		return -1;

	// Store previous front and move front one node ahead
	struct QNode* temp = q->front;

	*K = q->front->key;

	q->front = q->front->next;

	// If front becomes NULL, then change rear also as NULL
	if (q->front == NULL)
		q->rear = NULL;

	free(temp);
	return 1;
}

