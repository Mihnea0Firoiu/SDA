/*FIROIU Mihnea-Ioan 313CD*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Stack.h"

// Initiate stack
TStack initStack(Node_d *finger) {
    TStack stack = malloc(sizeof(*stack));
    if (stack == NULL) {
        fprintf(stderr, "Could not allocate stack!");
        exit(1);
    }
    stack->prev_finger = finger;
    stack->next = NULL;
    return stack;
}

// Push an element at the top of a stack
TStack push(TStack stack, Node_d *finger) {
    TStack top;
    if (stack == NULL) {
        return initStack(finger);
    }
    top = initStack(finger);
    top->next = stack;
    return top;
}

// Pop an element from the top of a stack
TStack pop(TStack stack) {
    TStack tmp;
    if (stack == NULL) {
        return stack;
    }
    tmp = stack;
    stack = stack->next;
    free(tmp);
    return stack;
}

// Returns the element at the top of a stack
Node_d *top(TStack stack) {
    if (stack == NULL) {
        exit(1);
    }
    return stack->prev_finger;
}

// Frees stack
TStack freeStack(TStack stack) {
    while (stack != NULL) {
        stack = pop(stack);
    }
    return NULL;
}
