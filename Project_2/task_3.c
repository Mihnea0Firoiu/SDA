/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <stdlib.h>
#include "func.h"

void task_3(char *in, char *out) {
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

    // Read input from file.
    unsigned int size = read_size(input);
    char *buffer = NULL;
    unsigned long long buffer_size = 0;
    read_tree(input, &buffer, &buffer_size);

    // Get tree.
    TQuadTree root = NULL;
    decompress(input, &root, buffer, buffer_size);

    /* For each subsection of the array it is enough to know the coordinates 
    of the top-left corner and down-right corner. */
    Point up_left, down_right;
    up_left.column = 0;
    up_left.row = 0;
    down_right.column = size - 1;
    down_right.row = size - 1;

    fprintf(output, "P6\n");
    fprintf(output, "%d %d\n", size, size);
    fprintf(output, "255\n");

    RGB *rgb_array = malloc(size * size * sizeof(RGB));
    get_array(&rgb_array, size, up_left, down_right, root);
    print_array(rgb_array, size, output);
    
    free_tree(&root);

    free(rgb_array);

    fclose(input);
    fclose(output);
    return;
}
