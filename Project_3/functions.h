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

void setup_Dijsktra(Graph *,Heap **, int, int, float **, int **, int **, int **,
 float **, char ***);
void free_structures(Heap **, int, int **, int **, float **, char ***, int **);
void Dijkstra(Graph *, int, int, int, float *, int, FILE *, int *);
void task2();

#endif
