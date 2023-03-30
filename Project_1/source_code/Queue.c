/*FIROIU Mihnea-Ioan 313CD*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 20

#include "Queue.h"

// Initiate node
Node_q *initNode_q(char *data) {
    Node_q *node = malloc(sizeof(Node_q));
    if (node == NULL) {
        fprintf(stderr, "Could not allocate queue node!");
        exit(1);
    }
    node->character = '\0';
    strcpy(node->data, data);
    node->next = NULL;
    return node;
}

// Initate queue
TQueue initQueue(char *data) {
    TQueue queue = malloc(sizeof(*queue));
    if (queue == NULL) {
        fprintf(stderr, "Could not allocate queue!");
        exit(1);
    }
    queue->head = initNode_q(data);
    queue->tail = queue->head;
    queue->size = 1;
}

// Verify if a queue is empty
int isEmpty(TQueue queue) {
    return queue == NULL || queue->head == NULL || queue->size == 0;
}

// Free node
Node_q *freeNode(Node_q *node) {
    if(node != NULL) {
        free(node);
    }
    return NULL;
}

// Insert a node at the end of a queue
TQueue enqueue(TQueue queue, char *data) {
    Node_q *node;
    if (isEmpty(queue)) {
        if (queue == NULL) {
            return initQueue(data);
        }
        free(queue);
        return initQueue(data);
    }
    node = initNode_q(data);
    queue->tail->next = node;
    queue->tail = node;
    queue->size++;
    return queue;
}

// Remove a node from the front of a queue
TQueue dequeue(TQueue queue) {
    Node_q *tmp;
    if (!isEmpty(queue)) {
        tmp = queue->head;
        queue->head = queue->head->next;
        tmp = freeNode(tmp);
        if (queue->head == NULL) {
            queue->tail = NULL;
        }
        queue->size--;
    }
    return queue;
}

// Free queue
TQueue freeQueue(TQueue queue) {
    while (!isEmpty(queue)) {
        queue = dequeue(queue);
    } if (queue != NULL) {
        free(queue);
    }
    return NULL;
}
