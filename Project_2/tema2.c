/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "tree.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Not enough arguments!\n");
        return -1;
    }

    if (strcmp(argv[1], "-c1") == 0) {
        if (argc < 4) {
            printf("Not enough arguments!\n");
            return -1;
        }
        unsigned char factor = argv[2][0];
        task_1(factor, argv[3], argv[4]);
        return 0;
    } else if (strcmp(argv[1], "-c2") == 0) {
        if (argc < 4) {
            printf("Not enough arguments!\n");
            return -1;
        }
        unsigned char factor = argv[2][0];
        task_2(factor, argv[3], argv[4]);
        return 0;
    } else if (strcmp(argv[1], "-d") == 0) {
        task_3(argv[2], argv[3]);
        return 0;
    }
    
    return 0;
}
