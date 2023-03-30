/*FIROIU Mihnea-Ioan 313CD*/

#ifndef QUEUE_H
#define QUEUE_H
#define MAX_LINE 20

typedef struct node_q {
    char data[MAX_LINE];
    char character;
    struct node_q *next;
} Node_q;

typedef struct queue {
    Node_q *head;
    Node_q *tail;
    int size;
} *TQueue;

Node_q *initNode_q(char *);
TQueue initQueue(char *);
Node_q *freeNode(Node_q *);
TQueue enqueue(TQueue, char *);
TQueue dequeue(TQueue);
TQueue freeQueue(TQueue);
#endif
