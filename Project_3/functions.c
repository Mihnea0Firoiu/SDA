/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Graph.h"
#include "Heap.h"
#include "functions.h"

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