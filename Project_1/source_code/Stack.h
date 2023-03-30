/*FIROIU Mihnea-Ioan 313CD*/

#ifndef STACK_H
#define STACK_H

typedef char T;
#include "DoublyLinkedListWSentinel.h"

typedef struct stack {
    Node_d *prev_finger;
    struct stack *next;
}*TStack;

TStack initStack(Node_d *);
TStack push(TStack, Node_d *);
TStack pop(TStack);
TStack freeStack(TStack);

#endif
