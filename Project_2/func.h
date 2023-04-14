/* FIROIU Mihnea-Ioan 313CD */

#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include "tree.h"

void read_type(FILE*);
int read_measurements(FILE*);
void read_colour_value(FILE*);
RGB *read_image(int, FILE*);
unsigned int read_size(FILE*);

typedef struct point {
    int row;
    int column;
} Point;

void build_image_tree(RGB *, int, Point, Point, TQuadTree *,
 unsigned long long);
void get_array(RGB **, int, Point, Point, TQuadTree);
void print_array(RGB*, int, FILE*);

void task_1(unsigned long long, char*, char*);
void task_2(unsigned long long, char*, char*);
void task_3(char*, char*);

#endif
