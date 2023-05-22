/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "Graph.h"
#include "Heap.h"
#include "functions.h"

#define INFINITY 100000
#define WORD_SIZE 20

int* reset_position(Heap *heap, int *position) {
    for (int i = 0; i < heap->size; i++) {
        position[heap->elem[i].data] = i;
    }
    return position;
}

void setup_Prim(Graph *graph, Heap *heap, int ***distance, int *position,
 int *visited, int root, int conex_comp) {
    if (conex_comp != 1) {
        *distance = realloc(*distance, sizeof(int *) * conex_comp);
        (*distance)[conex_comp - 1] = malloc(sizeof(int) * graph->node_num);
    }

    HContent content;
    for (int j = 0; j < graph->node_num; j++) {
        if (root != j) {
            (*distance)[conex_comp - 1][j] = INT_MAX;
            position[j] = j;
            
            content.data = j;
            content.prior = INT_MAX;
            insert_heap(heap, content);
        }
    }
    
    visited[root] = 1;
    (*distance)[conex_comp - 1][root] = 0;
    position[root] = root;

    content.data = root;
    content.prior = 0;
    insert_heap(heap, content);
    position = reset_position(heap, position);
}

void setup_Dijsktra(Graph *graph, Heap **heap, int M, int source, float **depth,
 int **d, int **position, int **parent, float **score, char ***path) {
    *d = malloc(graph->node_num * sizeof(int)); // distance
    *position = calloc(graph->node_num, sizeof(int));
	*parent = malloc(sizeof(int) * graph->node_num);
	for (int i = 0; i < graph->node_num; i++) {
		(*parent)[i] = -1;
	}
	*score = malloc(sizeof(float) * graph->node_num);
	*path = malloc(sizeof(char *) * graph->node_num);
	for (int i = 0; i < graph->node_num; i++) {
		(*path)[i] = malloc(sizeof(char) * WORD_SIZE);
	}

    make_queue(heap, M);

    HContent content;
	for (int i = 0; i < graph->node_num; i++) {
		if (i != source) {
			(*position)[i] = i;
			
			(*d)[i] = INFINITY;
			(*score)[i] = INFINITY;
            content.data = i;
            content.prior = INFINITY;
			
			insert_heap(*heap, content);
		}
	}
	
	// first element in heap
	(*position)[source] = source;

	(*d)[source] = 0;
	(*score)[source] = 0;
    content.data = source;
    content.prior = 0;

	insert_heap(*heap, content);
    *position = reset_position(*heap, *position);
}

void free_structures(Heap** heap, int N, int **parent, int **position,
 float **score, char ***path, int **d) {
    //free
	free_queue(*heap);
	free(*parent);
	free(*position);
	free(*score);
	for (int i = 0; i < N; i++) {
		free((*path)[i]);
	}
	free(*path);
	free(*d);
}
