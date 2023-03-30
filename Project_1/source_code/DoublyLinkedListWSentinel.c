/*FIROIU Mihnea-Ioan 313CD*/

#include <stdio.h>
#include <stdlib.h>

typedef char T;
#include "DoublyLinkedListWSentinel.h"

// Create node
Node_d *createNode() {
    Node_d *node = malloc(sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "Could not allocate list node!");
        exit(1);
    }
    node->next = NULL;
    node->prev = NULL;
    node->value = '#';
    return node;
}

// Initiate a doubly linked list with sentinel
TList initList() {
    TList list = malloc(sizeof(struct list));
    if (list == NULL) {
        fprintf(stderr, "Could not allocate list!");
        exit(1);
    }
    list->sentinel = calloc(1, sizeof(Node_d));
    if (list->sentinel == NULL) {
        fprintf(stderr, "Could not allocate sentinel!");
        exit(1);
    }
    list->sentinel->next = createNode();
    list->finger = list->sentinel->next;
    list->finger->prev = list->sentinel;
    return list;
}

// Move finger left
void moveLeft(TList list) {
    if (list->finger->prev == list->sentinel) {
        return;
    }
    list->finger = list->finger->prev;
}

// Move finger right
void moveRight(TList list) {
    if (list->finger->next == NULL) {
        Node_d *node = createNode();
        list->finger->next = node;
        node->prev = list->finger;
    }
    list->finger = list->finger->next;
}

// Write a certain value at the position of the finger
void write(TList list, T value) {
   list->finger->value = value; 
}

// Move finger left until you find a certain character
void moveLeftChar(TList list, T value, FILE* output) {
    Node_d *iter = list->finger;
    while (iter->value != value) {
        if (iter->prev == list->sentinel) {
            fprintf(output, "ERROR\n");
            return;
        }
        iter = iter->prev;
    }
    list->finger = iter;
}

// Move finger right until you find a certain character
void moveRightChar(TList list, T value) {
    Node_d *iter = list->finger;
    while (iter->value != value) {
        if (iter->next == NULL) {
            list->finger = iter;
            if (list->finger->next == NULL) {
                Node_d *node = createNode();
                list->finger->next = node;
                node->prev = list->finger;
            }
            list->finger = list->finger->next;
            return;
        }
        iter = iter->next;
    }
    list->finger = iter;
}

// Insert a character on the previous position of the finger
void insertLeft(TList list, T value, FILE* output) {
    if (list->finger->prev == list->sentinel) {
        fprintf(output, "ERROR\n");
        return;
    }
    Node_d *node = createNode();
    node->value = value;

    node->next = list->finger;
    node->prev = list->finger->prev;
    list->finger->prev->next = node;
    list->finger->prev = node;

    moveLeft(list);
}

// Insert a character on the next position of the finger
void insertRight(TList list, T value) {
    Node_d *node = createNode();
    node->value = value;

    node->prev = list->finger;
    node->next = list->finger->next;
    if (list->finger->next != NULL) {
        list->finger->next->prev = node;
    }
    list->finger->next = node;

    moveRight(list);
}

// Free list
TList freeList(TList list) {
    Node_d *iter = list->sentinel->next;
    Node_d *tmp = NULL;
    while (iter != NULL) {
        tmp = iter;
        iter = iter->next;
        free(tmp);
    }
    free(list->sentinel);
    free(list);
    return NULL;
}
