/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Graph.h"
#include "Heap.h"
#include "functions.h"

void Dijkstra(Graph *graph, int M, int source, int destination, FILE* output) {
    int *d = malloc(graph->node_num * sizeof(int)); // distance
    int *position = calloc(graph->node_num, sizeof(int));
    Heap *heap;
    make_queue(&heap, M);


    HContent content;
	for (int i = 0; i < graph->node_num; i++) {
		if (i != source) {
			d[i] = INT_MAX;
            content.data = i;
            content.prior = INT_MAX;
			insert_heap(heap, content);
		}
	}
	
	// first element in heap
	d[source] = 0;
    content.data = source;
    content.prior = 0;
	insert_heap(heap, content);
    reset_position(heap, position);

	while (heap->size != 0) {
		HContent min_node = heap->elem[0];
        remove_min(heap);

		List *temp = graph->adj[min_node.data];

		while (temp != NULL) {
			if (is_in_heap(heap, temp->data.value) != 0
			 && d[min_node.data] != INT_MAX
			 && d[min_node.data] + temp->data.cost < d[temp->data.value]) {

				d[temp->data.value] = d[min_node.data] + temp->data.cost;
                sift_up(heap, position[temp->data.value]);
                reset_position(heap, position);
			}
			temp = temp->next;
		}
	}
	printf("\n");
	printf("Varf	Drum minim\n");
	for (int i = 0; i < graph->node_num; i++) {
		printf("%d    %d\n", i, d[i]);
	}
	free(d);
}

void task2() {
    FILE *input = fopen("tema3.in", "r");
    FILE *output = fopen("tema3.out", "w");

    int N, M;
    fscanf(input, "%d %d", &N, &M);

    Graph *graph;
    init_graph(&graph, N, 1);
    read_graph(graph, input, M);
    
    Prim(graph, M, output);

    free_graph(graph);

    fclose(input);
    fclose(output);
}
