/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "Graph.h"
#include "Heap.h"
#include "functions.h"

#define INFINITY 100000
#define WORD_SIZE 20

void Dijkstra(Graph *graph, int M, int source, int destination,
 float *depth, int treasure_mass, FILE* output, int *ok) {
    int *d, *position, *parent; // distance, positon and parent
	char **path; // path
	float *score; // score
    Heap *heap;
    
	setup_Dijkstra(graph, &heap, M, source, &depth, &d, &position, &parent,
	 &score, &path);
	// Dijkstra begins here
	while (heap->size != 0) {
		HContent min_node = heap->elem[0];
        remove_min(heap);
		position = reset_position(heap, position);

		List *temp = graph->adj[min_node.data];

		while (temp != NULL) {
			int value = temp->data.value;
			float temp_score = temp->data.cost / depth[value];
			if (is_in_heap(heap, value) != 0
			 && score[min_node.data] != INFINITY
			 && score[min_node.data] + temp_score < score[value]) {

				parent[value] = min_node.data;

				score[value] = score[min_node.data] + temp_score;
				d[value] = d[min_node.data] + temp->data.cost;
				heap->elem[position[value]].prior = score[value];
                
				sift_up(heap, position[value]);
                position = reset_position(heap, position);

			}
			temp = temp->next;
		}
	}

	if (d[destination] == INFINITY) {
		if (strcmp(graph->node_names[destination], "Corabie") == 0) {
			fprintf(output,
			 "Echipajul nu poate transporta comoara inapoi la corabie\n");
			free_structures(&heap, graph->node_num, &parent, &position, &score,
			 &path, &d);

			return;
		} else if (strcmp(graph->node_names[destination], "Insula") == 0) {
			fprintf(output, "Echipajul nu poate ajunge la insula\n");
			*ok = 1;
			free_structures(&heap, graph->node_num, &parent, &position, &score,
			 &path, &d);
			return;
		}
	// if the destination is "Insula", the function only checks if there is a
	// path between "Corabie" and "Insula"
	} else if (strcmp(graph->node_names[destination], "Insula") == 0) {
		free_structures(&heap, graph->node_num, &parent, &position, &score,
	 	 &path, &d);
		return;
	}

	int min_depth = INFINITY;
	int count = 0;
	int node = parent[destination];
	// build the path array
	strcpy(path[count], graph->node_names[destination]);
	count++;
	
	while (node != -1) {
		if (min_depth > depth[node] && node != source) {
			min_depth = depth[node];
		}
		strcpy(path[count], graph->node_names[node]);
		node = parent[node];
		count++;
	}

	// start print
	for (int i = count - 1; i >= 0; i--) {
		fprintf(output, "%s ", path[i]);
	}
	fprintf(output, "\n");
	fprintf(output, "%d\n", d[destination]);
	fprintf(output, "%d\n", min_depth);
	fprintf(output, "%d\n", treasure_mass / min_depth);

	free_structures(&heap, graph->node_num, &parent, &position, &score,
	 &path, &d);
}

void task2() {
    FILE *input = fopen("tema3.in", "r");
    FILE *output = fopen("tema3.out", "w");

    int N, M;
    fscanf(input, "%d %d", &N, &M);

    Graph *graph;
    init_graph(&graph, N, 1);
    read_graph(graph, input, M);

	float *depth = malloc(sizeof(float) * N);

    read_depth(graph, &depth, N, input);

	int source, destination;
	for (int i = 0; i < N; i++) {
		if (strcmp("Insula", graph->node_names[i]) == 0) {
            source = i;
        } else if (strcmp("Corabie", graph->node_names[i]) == 0) {
			destination = i;
		}
	}
    
	int treasure_mass;
	fscanf(input, "%d", &treasure_mass);

	int ok = 0;
	// check first if there is a path between "Corabie" and "Insula"
	Dijkstra(graph, M, destination, source, depth, treasure_mass, output, &ok);
	if (ok != 1) {
		Dijkstra(graph, M, source, destination, depth, treasure_mass, output,
		 &ok);
	}
    free_graph(graph);
	free(depth);

    fclose(input);
    fclose(output);
}
