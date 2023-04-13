/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <stdlib.h>
#include "func.h"

void task_2(unsigned long long factor, char *in, char *out) {
    FILE* input = fopen(in, "rb");
    FILE* output = fopen(out, "wb");
    if (input == NULL) {
        printf("No input file!\n");
        exit(1);
    }
    if (output == NULL) {
        printf("No output file!\n");
        exit(1);
    }

    read_type(input);
    unsigned int measurements = read_measurements(input);
    read_colour_value(input);
    RGB *rgb_array = read_image(measurements, input);

    Point up_left, down_right;
    up_left.column = 0;
    up_left.row = 0;
    down_right.column = measurements - 1;
    down_right.row = measurements - 1;

    TQuadTree root = NULL;
    build_image_tree(rgb_array, measurements, up_left, down_right, &root,
     factor);
    int level_number = height(root) + 1;

    compress(root, level_number, measurements, output);
    
    fclose(input);
    fclose(output);
    return;
}
