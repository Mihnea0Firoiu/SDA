/* FIROIU Mihnea-Ioan 313CD */

#ifndef TREE_H
#define TREE_H

#include <stdio.h>


typedef struct __attribute__((packed)) {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} RGB;

typedef struct node {
    unsigned char node_type;
    RGB rgb;
    struct node* up_left;
    struct node* up_right;
    struct node* down_right;
    struct node* down_left;
} Node, *TQuadTree;

void create_tree(TQuadTree *);
int height(TQuadTree);
int leaf_num(TQuadTree);
int min_height(TQuadTree);
void print_level(TQuadTree, int, FILE*);
void compress(TQuadTree, int, int, FILE*);
void read_tree(FILE*, char **, int*);
void insert(TQuadTree*, unsigned char, unsigned char, RGB);
void decompress(FILE*, TQuadTree*, char*, int);

#endif
