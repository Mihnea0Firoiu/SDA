/*FIROIU Mihnea-Ioan 313CD*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Queue.h"

// Initiate node
Node_q *init_node_q(TQuadTree tree) {
    Node_q *node = malloc(sizeof(Node_q));
    if (node == NULL) {
        fprintf(stderr, "Could not allocate queue node!");
        exit(1);
    }
    node->tree = tree;
    node->next = NULL;
    return node;
}

// Initate queue
TQueue init_queue(TQuadTree tree) {
    TQueue queue = malloc(sizeof(*queue));
    if (queue == NULL) {
        fprintf(stderr, "Could not allocate queue!");
        exit(1);
    }
    queue->head = init_node_q(tree);
    queue->tail = queue->head;
    queue->size = 1;
    return queue;
}

// Verify if a queue is empty
int is_empty(TQueue queue) {
    return queue == NULL || queue->head == NULL || queue->size == 0;
}

// Free node
Node_q *free_node(Node_q *node) {
    if(node != NULL) {
        free(node);
    }
    return NULL;
}

// Insert a node at the end of a queue
TQueue enqueue(TQueue queue, TQuadTree tree) {
    Node_q *node;
    if (is_empty(queue)) {
        if (queue == NULL) {
            return init_queue(tree);
        }
        free(queue);
        return init_queue(tree);
    }
    node = init_node_q(tree);
    queue->tail->next = node;
    queue->tail = node;
    queue->size++;
    return queue;
}

// Remove a node from the front of a queue
TQueue dequeue(TQueue queue) {
    Node_q *tmp;
    if (!is_empty(queue)) {
        tmp = queue->head;
        queue->head = queue->head->next;
        tmp = free_node(tmp);
        if (queue->head == NULL) {
            queue->tail = NULL;
        }
        queue->size--;
    }
    return queue;
}

// Free queue
TQueue free_queue(TQueue queue) {
    while (!is_empty(queue)) {
        queue = dequeue(queue);
    } if (queue != NULL) {
        free(queue);
    }
    return NULL;
}
