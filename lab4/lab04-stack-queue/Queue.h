#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	Item elem;
	struct QueueNode *next;
}QueueNode;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	long size;
}Queue;

Queue* createQueue(void){
	// TODO: Cerinta 2
	Queue* queue = malloc(sizeof(* queue));
	queue->size = 0;
	queue->front = NULL;
	queue->rear = NULL;
	return queue;
} 

int isQueueEmpty(Queue *q){
	// TODO: Cerinta 2
	return q->front == NULL;
}

void enqueue(Queue *q, Item elem){
	// TODO: Cerinta 2
	if (q == NULL) {
		q = createQueue();
	}
	QueueNode *node = malloc (sizeof(*node));
	node->elem = elem;
	node->next = NULL;
	if (isQueueEmpty(q)) {
		q->front = node;
		q->rear = node;
	} else {
		q->rear->next = node;
		q->rear = q->rear->next;
	}
	q->size++;
}

Item front(Queue* q){
	// TODO: Cerinta 2
	return q->front->elem;
}

void dequeue(Queue* q){
	// TODO: Cerinta 2
	if (isQueueEmpty(q)) {
		return;
	}
	QueueNode *tmp = q->front;
	q->front = tmp->next;
	if (q->size == 1) {
		q->rear = NULL;
	}
	q->size--;
	free(tmp);
}

void destroyQueue(Queue *q){
	// TODO: Cerinta 2
	while (!isQueueEmpty(q)) {
		dequeue(q);
	}
	free(q);
}

#endif
