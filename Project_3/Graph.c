/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "Graph.h"

#define WORD_SIZE 20

void init_graph(Graph **graph, int node_num, int type) {
    *graph = malloc(sizeof(Graph));
    (*graph)->node_num = node_num;
    (*graph)->type = type;
    (*graph)->adj = calloc(node_num, sizeof(List *));
    (*graph)->node_names = calloc(node_num, sizeof(char *));
}

void convert(Graph *graph, char *first_node, char *second_node, int *value_1,
 int *value_2) {
    *value_1 = -1;
    *value_2 = -1;
    for (int i = 0; i < graph->node_num; i++) {
        if (graph->node_names[i] == NULL && *value_1 == -1) {
            *value_1 = i;
            graph->node_names[i] = strdup(first_node);
            if (*value_2 != -1) {
                return;
            }
        } else if (graph->node_names[i] == NULL && *value_2 == -1) {
            *value_2 = i;
            graph->node_names[i] = strdup(second_node);
            if (*value_1 != -1) {
                return;
            }
        } else if (strcmp(graph->node_names[i], first_node) == 0) {
            *value_1 = i;
            if (*value_2 != -1) {
                return;
            }
        } else if (strcmp(graph->node_names[i], second_node) == 0) {
            *value_2 = i;
            if (*value_1 != -1) {
                return;
            }
        }
    }
}

void insert_graph(Graph *graph, int value_1, int value_2, int cost) {
    List *node = malloc(sizeof(List));
    node->data.cost = cost;
    node->data.value = value_2;

    // insert on the first position
    node->next = graph->adj[value_1];
    graph->adj[value_1] = node;

    if (graph->type == 0) { // graph is undirected
        List *node_1 = malloc(sizeof(List));
        node_1->data.cost = cost;
        node_1->data.value = value_1;

        // insert on the first position
        node_1->next = graph->adj[value_2];
        graph->adj[value_2] = node_1;
    }
}

void read_graph(Graph *graph, FILE *input, int M) {
    char first_node[WORD_SIZE];
    char second_node[WORD_SIZE];
    int cost, value_1, value_2;
    for (int i = 0; i < M; i++) {
        fscanf(input, "%s %s %d", first_node, second_node, &cost);
        
        convert(graph, first_node, second_node, &value_1, &value_2);
        insert_graph(graph, value_1, value_2, cost);
    }
}

void read_depth(Graph *graph, float **depth, int N, FILE *input) {
    char node[WORD_SIZE];
    int d;
    for (int i = 0; i < N; i++) {
        fscanf(input, "%s %d", node, &d);
        for (int j = 0; j < N; j++) {
            if (strcmp(node, graph->node_names[j]) == 0) {
                (*depth)[j] = d;
            }
        }
    }
}

int get_cost(Graph *graph, int value_1, int value_2) {
    List *temp = graph->adj[value_1];
    while (temp != NULL) {
        if (temp->data.value == value_2) {
            return temp->data.cost;
        }
        temp = temp->next;
    }
    return INT_MAX;
}

void free_graph(Graph *graph) {
    for (int i = 0; i < graph->node_num; i++) {
        List *tmp = graph->adj[i];
        if (tmp == NULL) {
            continue;
        }

        List *aux = tmp->next;
        while (aux != NULL) {
            free(tmp);
            tmp = aux;
            aux = aux->next;
        }
        free(tmp);
    }
    free(graph->adj);
    for (int i = 0; i < graph->node_num; i++) {
        free(graph->node_names[i]);
    }
    free(graph->node_names);
    free(graph);
}
