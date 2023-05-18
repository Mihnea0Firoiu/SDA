/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <string.h>
#include "functions.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No argument!\n");
        return 0;
    }
    if (strcmp(argv[1], "1") == 0) {
        task1();
        return 0;
    } else if (strcmp(argv[1], "2") == 0) {
        task2();
        return 0;
    }
    return 0;
}
