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
    *distance = realloc(*distance, sizeof(int *) * conex_comp);
    (*distance)[conex_comp - 1] = malloc(sizeof(int) * graph->node_num);

    for (int i = 0; i < graph->node_num; i++) {
        (*distance)[conex_comp - 1][i] = INT_MAX;
    }
    visited[root] = 1;
    (*distance)[conex_comp - 1][root] = 0;
    heap->elem[position[root]].prior = 0;

    sift_up(heap, position[root]);
    position = reset_position(heap, position);
}

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

            if (conex_comp != 1) {
                distance = realloc(distance, sizeof(int *) * conex_comp);
                distance[conex_comp - 1] = malloc(sizeof(int) * graph->node_num);
            }
            for (int j = 0; j < graph->node_num; j++) {
                distance[conex_comp - 1][j] = INT_MAX;
            }
            HContent content;
            
            visited[i] = 1;
            distance[conex_comp - 1][i] = 0;

            content.data = i;
            content.prior = 0;
            insert_heap(heap, content);
            reset_position(heap, position);

            while (heap->size != 0) {
                HContent min_node = heap->elem[0];
                remove_min(heap);
                reset_position(heap, position);
                //fprintf(output, "%d %d   ", min_node.data, min_node.prior);
                List *temp = graph->adj[min_node.data];
                while (temp != NULL) {
                    int value = temp->data.value;
                    if (visited[value] == 0
                     && temp->data.cost < distance[conex_comp - 1][value]) {
                        visited[value] = 1;
                        distance[conex_comp - 1][value] = temp->data.cost;
                        content.data = value;
                        content.prior = temp->data.cost;

                        insert_heap(heap, content);
                        position = reset_position(heap, position);
                        //fprintf(output, "%d %d      ", value, distance[conex_comp - 1][value]);
                        
                    } else if (is_in_heap(heap, value) != 0
                     && temp->data.cost < distance[conex_comp - 1][value]) {
                        distance[conex_comp - 1][value] = temp->data.cost;
                        heap->elem[position[value]].prior = temp->data.cost;

                        sift_up(heap, position[value]);
                        position = reset_position(heap, position);
                        // ?
                        //fprintf(output, "%d %d      ", value, distance[conex_comp - 1][value]);
                    }
                    
                    temp = temp->next;
                }
            }
            //fprintf(output, "\n");
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
                //fprintf(output, "%d %d      ", j, distance[i][j]);
            }
            
        }
        //fprintf(output, "\n");
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

void Dijkstra(Graph *graph) {

}

void task2() {
    FILE *input = fopen("tema3.in", "r");
    FILE *output = fopen("tema3.out", "w");



    fclose(input);
    fclose(output);
}
