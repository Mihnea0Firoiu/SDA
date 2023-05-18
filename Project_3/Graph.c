/* FIROIU Mihnea-Ioan 313CD */

#include <stdlib.h>
#include <limits.h>
#include "Graph.h"

void init_graph(Graph **graph, int node_num, int type) {
    *graph = malloc(sizeof(Graph));
    (*graph)->node_num = node_num;
    (*graph)->type = type;
    (*graph)->adj = calloc(node_num, sizeof(List *));
}

void insert_graph(Graph *graph, int u, int value, int cost, int type) {
    List *node = malloc(sizeof(List));
    node->data.cost = cost;
    node->data.value = value;

    // insert on the first position
    node->next = graph->adj[u];
    graph->adj[u] = node;

    if (type == 0) { // graph is undirected
        List *node_1 = malloc(sizeof(List));
        node_1->data.cost = cost;
        node_1->data.value = u;

        // insert on the first position
        node_1->next = graph->adj[value];
        graph->adj[value] = node_1;
    }
}

int get_cost(Graph *graph, int u, int value) {
    List *temp = graph->adj[u];
    while (temp != NULL) {
        if (temp->data.value == value) {
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
    free(graph);
}
