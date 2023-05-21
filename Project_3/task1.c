/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Graph.h"
#include "Heap.h"
#include "functions.h"

void Prim(Graph* graph, int M, FILE* output) {
    int **distance = malloc(sizeof(int *));
    distance[0] = malloc(sizeof(int) * graph->node_num);

    int *visited = calloc(graph->node_num, sizeof(int));
    int *position = calloc(graph->node_num, sizeof(int));

    int conex_comp = 0;

    for (int i = 0; i < graph->node_num; i++) {
        if (visited[i] == 0) {
            Heap *heap;
            make_queue(&heap, M);
            conex_comp++;

            setup_Prim(graph, heap, &distance, position, visited, i,
             conex_comp);

            while (heap->size != 0) {
                HContent min_node = heap->elem[0];
                if (min_node.prior == INT_MAX) {
                    break;
                }

                remove_min(heap);
                reset_position(heap, position);

                List *temp = graph->adj[min_node.data];
                while (temp != NULL) {
                    int value = temp->data.value;
                    if (is_in_heap(heap, value) != 0
                     && temp->data.cost < distance[conex_comp - 1][value]) {

                        distance[conex_comp - 1][value] = temp->data.cost;
                        heap->elem[position[value]].prior = temp->data.cost;
                        visited[value] = 1;

                        sift_up(heap, position[value]);
                        position = reset_position(heap, position);
                        sift_down(heap, position[value]);
                        position = reset_position(heap, position);
                    }
                    temp = temp->next;
                }
            }
            free_queue(heap);
        }
    }


    fprintf(output, "%d\n", conex_comp);

    int *distance_out = malloc(sizeof(int) * conex_comp);
    for (int i = 0; i < conex_comp; i++) {
        int sum = 0;
        for (int j = 0; j < graph->node_num; j++) {
            if (distance[i][j] != INT_MAX) {
                sum += distance[i][j];
            }
            
        }
        distance_out[i] = sum;
    }

    //sort vector
    for (int i = 0; i < conex_comp - 1; i++) {
        for (int j = i + 1; j < conex_comp; j++) {
            if (distance_out[i] > distance_out[j]) {
                int aux = distance_out[i];
                distance_out[i] = distance_out[j];
                distance_out[j] = aux;
            }
        }
    }
    
    for (int i = 0; i < conex_comp; i++) {
        fprintf(output, "%d\n", distance_out[i]);
    }
    free(distance_out);
    for (int i = 0; i < conex_comp; i++) {
        free(distance[i]);
    }
    free(distance);
    free(visited);
    free(position);
    
}

void task1() {
    FILE *input = fopen("tema3.in", "r");
    FILE *output = fopen("tema3.out", "w");

    int N, M;
    fscanf(input, "%d %d", &N, &M);

    Graph *graph;
    init_graph(&graph, N, 0);
    read_graph(graph, input, M);
    
    Prim(graph, M, output);

    free_graph(graph);

    fclose(input);
    fclose(output);
}
