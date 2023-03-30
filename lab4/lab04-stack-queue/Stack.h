#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode{
	Item elem;
	struct StackNode *next;
} StackNode;

typedef struct Stack{
	StackNode* head;  // Varful stivei
	long size; // Numarul de elemente din stiva
} Stack;

Stack* createStack(void){
	// TODO: Cerinta 1
	Stack *stack = malloc(sizeof(*stack));
	stack->size = 0;
	stack->head = NULL;
	return stack;
}

int isStackEmpty(Stack* stack){
	// TODO: Cerinta 1
	return stack->head == NULL && stack->size == 0;
}

void push(Stack *stack, Item elem){
	// TODO: Cerinta 1
	StackNode *node = malloc(sizeof(* node));
	node->elem = elem;
	node->next = stack->head;
	stack->head = node;
	stack->size++;
}

Item top(Stack *stack){	
	// TODO: Cerinta 1
	return stack->head->elem;
} 

void pop(Stack *stack){
	// TODO: Cerinta 1
	if (isStackEmpty(stack)) {
		return;
	}
	StackNode *tmp = stack->head;
	stack->head = stack->head->next;
	free(tmp);
	stack->size--;
}

void destroyStack(Stack *stack){
	// TODO: Cerinta 1
	while (stack->head != NULL) {
		pop(stack);
	}
	free(stack);
}

#endif 
