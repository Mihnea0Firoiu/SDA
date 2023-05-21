/* FIROIU Mihnea-Ioan 313CD */

#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>

typedef struct graph_content {
    int value;
    int cost;
} GContent;

typedef struct list {
    GContent data;
    struct list *next;
} List;

typedef struct graph {
    int node_num;
    // 0 for undirected graphs and 1 for directed graphs
    int type;
    char **node_names;
    List **adj;
} Graph;

void init_graph(Graph **, int, int);
void convert(Graph *, char *, char *, int *, int *);
void insert_graph(Graph *, int, int, int);
void read_graph(Graph *, FILE *, int);
int get_cost(Graph *, int, int);
void free_graph(Graph *);

#endif
