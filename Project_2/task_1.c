/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "tree.h"

void task_1(unsigned char factor, char *in, char *out) {
    FILE* input = fopen(in, "rb");
    FILE* output = fopen(out, "w");
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
    down_right.column = measurements;
    down_right.row = measurements;

    TQuadTree root;
    build_image_tree(rgb_array, measurements, up_left, down_right, &root, factor);

    fclose(input);
    fclose(output);
}
