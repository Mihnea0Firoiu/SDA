/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void create_tree(TQuadTree* root) {
    (*root) = calloc(1, sizeof(Node));
}

int height(TQuadTree root) {
    if (root == NULL) {
        return 0;
    }
    if (root->up_left == NULL
     && root->up_right == NULL
     && root->down_right == NULL
     && root->down_left == NULL) {
        return 0;
    }
    int up_left, up_right, down_right, down_left;
    
    up_left = height(root->up_left);
    up_right = height(root->up_right);
    down_right = height(root->down_right);
    down_left = height(root->down_left);

    if (up_left >= up_right && up_left >= down_left && up_left >= down_right) {
        return up_left + 1;
    } else if (up_right >= up_left && up_right >= down_left
     && up_right >= down_right) {
        return up_right + 1;
    } else if (down_left >= up_left && down_left >= up_right
     && down_left >= down_right) {
        return down_left + 1;
    } else if (down_right >= up_left && down_right >= up_right
     && down_right >= down_left) {
        return down_right + 1;
    }
    return 0;
}

int leaf_num(TQuadTree root) {
    if (root == NULL) {
        return 0;
    }
    if (root->up_left == NULL
     && root->up_right == NULL
     && root->down_right == NULL
     && root->down_left == NULL) {
        return 1;
    }
    if (root->node_type == 0) {
        return leaf_num(root->up_left) + leaf_num(root->up_right)
         + leaf_num(root->down_right) + leaf_num(root->down_left);
    }
    return 0;
}

int min_height(TQuadTree root) {
    if (root == NULL) {
        return 0;
    }
    if (root->up_left == NULL
     && root->up_right == NULL
     && root->down_right == NULL
     && root->down_left == NULL) {
        return 0;
    }
    int up_left, up_right, down_right, down_left;
    
    up_left = min_height(root->up_left);
    up_right = min_height(root->up_right);
    down_right = min_height(root->down_right);
    down_left = min_height(root->down_left);

    if (up_left <= up_right && up_left <= down_left && up_left <= down_right) {
        return up_left + 1;
    } else if (up_right <= up_left && up_right <= down_left
     && up_right <= down_right) {
        return up_right + 1;
    } else if (down_left <= up_left && down_left <= up_right
     && down_left <= down_right) {
        return down_left + 1;
    } else if (down_right <= up_left && down_right <= up_right
     && down_right <= down_left) {
        return down_right + 1;
    }
    return 0;
}

void print_level(TQuadTree root, int level, FILE* output) {
    if (root == NULL) {
        return;
    }
    if (level == 0) {
        fwrite(&root->node_type, sizeof(char), 1, output);
        if (root->node_type == 1) {
            //fwrite(&root->rgb, sizeof(RGB), 1, output);
            fwrite(&root->rgb.red, sizeof(unsigned char), 1, output);
            fwrite(&root->rgb.green, sizeof(unsigned char), 1, output);
            fwrite(&root->rgb.blue, sizeof(unsigned char), 1, output);
        }
    }
    print_level(root->up_left, level - 1, output);
    print_level(root->up_right, level - 1, output);
    print_level(root->down_right, level - 1, output);
    print_level(root->down_left, level - 1, output);
}

void compress(TQuadTree root, int level_number, int measurements, FILE* output) {
    fwrite(&measurements, sizeof(unsigned int), 1, output);
    for (int i = 0; i < level_number; i++) {
        print_level(root, i, output);
    }
}

void read_tree(FILE* input, char **buffer, int *buffer_size) {
    fseek(input, 0, SEEK_END);
    *buffer_size = ftell(input);
    fseek(input, 0, SEEK_SET);
    *buffer = malloc(*buffer_size);
    fread(*buffer, *buffer_size, 1, input);
    
}

void insert(TQuadTree *root, unsigned char parent_type, unsigned char type, RGB rgb) {
    if (*root == NULL && parent_type == 0) {
        create_tree(root);
        (*root)->node_type = type;
        (*root)->rgb = rgb;
        return;
    } else if (*root == NULL) {
        return;
    }
    parent_type = (*root)->node_type;
}

void decompress(FILE* input, TQuadTree* root, char* buffer, int buffer_size) {
    if (*root == NULL) {
        create_tree(root);
    }
    for (int i = 0; i < buffer_size; i++) {
        unsigned char type = buffer[i];
        if (type == 0) {

        }
    }
}
