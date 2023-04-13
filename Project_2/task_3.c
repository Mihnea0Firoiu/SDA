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

    unsigned int size = read_size(input);
    char *buffer = NULL;
    int buffer_size = 0;
    read_tree(input, &buffer, &buffer_size);
    //fwrite(buffer, buffer_size, 1, output);
    
    TQuadTree root = NULL;
    decompress(input, &root, buffer, buffer_size);

    //fprintf(output, "P6\n");
    fclose(input);
    fclose(output);
    return;
}
