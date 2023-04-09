/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <stdlib.h>
#include "task_1.h"
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
    TQuadTree root;
    create_tree(&root);

    fclose(input);
    fclose(output);
}
