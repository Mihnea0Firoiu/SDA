/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"
#include "tree.h"

void read_type(FILE* input) {
    char file_type[2];
    fscanf(input, "%s", file_type);
    if (strcmp(file_type, "P6") != 0) {
        printf("Warning! Wrong file type!\n");
        exit(1);
    }
}

int read_measurements(FILE* input) {
    unsigned int width, height;
    fscanf(input, "%u %u", &width, &height);
    if (width != height) {
        printf("Warning! The image is not a square!\n");
        exit(1);
    }
    return width;
}

void read_colour_value(FILE* input) {
    int colour_value;
    fscanf(input, "%d", &colour_value);
    if (colour_value != 255) {
        printf("Warning! The maximum colour value is bigger than 255!");
        exit(1);
    }
}

RGB *read_image(int measurements, FILE* input) {
    RGB *rgb_array = malloc(measurements * measurements * sizeof(RGB));
    fscanf(input, "\n");
    fread(rgb_array, sizeof(RGB), measurements * measurements, input);
    return rgb_array;
}

void build_image_tree(RGB *rgb_array, int dim, Point up_left, Point down_right,
 TQuadTree *root, unsigned long long factor) {
    if ((*root) == NULL) {
        create_tree(root);
    }

    unsigned long long red = 0, green = 0, blue = 0;
    int column = down_right.column - up_left.column + 1;
    for (int i = up_left.row; i <= down_right.row; i++) {
        for (int j = up_left.column; j <= down_right.column; j++) {
            red = red + rgb_array[i * dim + j].red;
            green = green + rgb_array[i * dim + j].green;
            blue = blue + rgb_array[i * dim + j].blue;
        }
    }

    red = red / (column * column);
    green = green / (column * column);
    blue = blue / (column * column);
    unsigned long long mean = 0;

    for (int i = up_left.row; i <= down_right.row; i++) {
        for (int j = up_left.column; j <= down_right.column; j++) {
            mean = mean + (red - rgb_array[i * dim + j].red) *
             (red - rgb_array[i * dim + j].red)
             + (green - rgb_array[i * dim + j].green)
             * (green - rgb_array[i * dim + j].green)
             + (blue - rgb_array[i * dim + j].blue)
             * (blue - rgb_array[i * dim + j].blue);
        }
    }
    
    mean = mean / (3 * column * column);

    if (mean <= factor) {
        (*root)->node_type = 1;
        (*root)->rgb.red = (unsigned char)red;
        (*root)->rgb.green = (unsigned char)green;
        (*root)->rgb.blue = (unsigned char)blue;
        return ;
    } else {
        Point up_left_copy, down_right_copy;

        // Up_left
        up_left_copy.row = up_left.row;
        up_left_copy.column = up_left.column;
        down_right_copy.row = (up_left.row + down_right.row) / 2;
        down_right_copy.column = (up_left.column + down_right.column) / 2;
        build_image_tree(rgb_array, dim, up_left_copy, down_right_copy,
         &((*root)->up_left), factor);

        // Up_right
        up_left_copy.row = up_left.row;
        up_left_copy.column = 1 + (up_left.column + down_right.column) / 2;
        down_right_copy.row = (up_left.row + down_right.row) / 2;
        down_right_copy.column = down_right.column;
        build_image_tree(rgb_array, dim, up_left_copy, down_right_copy,
         &((*root)->up_right), factor);

        // Down_right
        up_left_copy.row = 1 + (up_left.row + down_right.row) / 2;
        up_left_copy.column = 1 + (up_left.column + down_right.column) / 2;
        down_right_copy.row = down_right.row;
        down_right_copy.column = down_right.column;
        build_image_tree(rgb_array, dim, up_left_copy, down_right_copy,
         &((*root)->down_right), factor);

        // Down_left
        up_left_copy.row = 1 + (up_left.row + down_right.row) / 2;
        up_left_copy.column = up_left.column;
        down_right_copy.row = down_right.row;
        down_right_copy.column = (up_left.column + down_right.column) / 2;
        build_image_tree(rgb_array, dim, up_left_copy, down_right_copy,
         &((*root)->down_left), factor);
    }
}

unsigned int read_size(FILE* input) {
    unsigned int size;
    fread(&size, sizeof(unsigned int), 1, input);
    return size;
}
