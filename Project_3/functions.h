/* FIROIU Mihnea-Ioan 313CD */

#ifndef FUNCTiONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include "Graph.h"
#include "Heap.h"

int* reset_position(Heap *, int *);
void setup_Prim(Graph *, Heap *, int ***, int *, int *, int, int);
void Prim(Graph *, int, FILE *);
void task1();

void Dijkstra(Graph *, int, int, int, FILE *);
void task2();

#endif
