/*FIROIU Mihnea-Ioan 313CD*/

#ifndef DOUBLY_LINKED_LIST_W_SENTINEL_H
#define DOUBLY_LINKED_LIST_W_SENTINEL_H

typedef struct node_d {
    T value;
    struct node_d* prev;
    struct node_d* next;
} Node_d;

typedef struct list {
    Node_d *sentinel;
    Node_d *finger;
} *TList;

Node_d *createNode();
TList initList();
void moveLeft(TList);
void moveRight(TList);
void write(TList, T);
void moveLeftChar(TList, T, FILE*);
void moveRightChar(TList, T);
void insertLeft(TList, T, FILE*);
void insertRight(TList, T);
TList freeList(TList);
#endif