/*FIROIU Mihnea-Ioan 313CD*/

#ifndef QUEUE_H
#define QUEUE_H

typedef struct node *TQuadTree;

typedef struct node_q {
    TQuadTree tree;
    struct node_q *next;
} Node_q;

typedef struct queue {
    Node_q *head;
    Node_q *tail;
    int size;
} *TQueue;

Node_q *init_node_q(TQuadTree);
TQueue init_queue(TQuadTree);
int is_empty(TQueue);
Node_q *free_node(Node_q *);
TQueue enqueue(TQueue, TQuadTree);
TQueue dequeue(TQueue);
TQueue free_queue(TQueue);
#endif
