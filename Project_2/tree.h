/* FIROIU Mihnea-Ioan 313CD */

#ifndef TREE_H
#define TREE_H

typedef struct node {
    unsigned char node_type;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    struct node* up_left;
    struct node* up_right;
    struct node* down_right;
    struct node* down_left;
} Node, *TQuadTree;

void create_tree(TQuadTree *);


#endif
