/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "Queue.h"

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
            fwrite(&root->rgb, sizeof(RGB), 1, output);
        }
    }
    print_level(root->up_left, level - 1, output);
    print_level(root->up_right, level - 1, output);
    print_level(root->down_right, level - 1, output);
    print_level(root->down_left, level - 1, output);
}

void compress(TQuadTree root, int level_number, int measurements,
 FILE* output) {
    fwrite(&measurements, sizeof(unsigned int), 1, output);
    for (int i = 0; i < level_number; i++) {
        print_level(root, i, output);
    }
}

void read_tree(FILE* input, char **buffer, unsigned long long *buffer_size) {
    fseek(input, 0, SEEK_END);
    *buffer_size = ftell(input) - sizeof(unsigned int);
    fseek(input, sizeof(unsigned int), SEEK_SET);
    *buffer = malloc(*buffer_size);
    fread(*buffer, *buffer_size, 1, input);
    
}

TQuadTree insert(TQuadTree root, unsigned char type, RGB rgb, TQueue* queue) {
    if (root == NULL) {
        create_tree(&root);
        root->node_type = type;
        root->rgb = rgb;
        *queue = init_queue(root);
        return root;
    }
    
    while (is_empty(*queue) == 0) {

        TQuadTree head = (*queue)->head->tree;

        if (head->up_left == NULL) {

            create_tree(&head->up_left);
            head->up_left->node_type = type;
            head->up_left->rgb = rgb;
            if (type != 1) {
                *queue = enqueue(*queue, head->up_left);
            }
            return root;
        }

        if (head->up_right == NULL) {

            create_tree(&head->up_right);
            head->up_right->node_type = type;
            head->up_right->rgb = rgb;
            if (type != 1) {
                *queue = enqueue(*queue, head->up_right);
            }
            return root;
        }

        if (head->down_right == NULL) {

            create_tree(&head->down_right);
            head->down_right->node_type = type;
            head->down_right->rgb = rgb;
            if (type != 1) {
                *queue = enqueue(*queue, head->down_right);
            }
            return root;
        }
        
        if (head->down_left == NULL) {

            create_tree(&head->down_left);
            head->down_left->node_type = type;
            head->down_left->rgb = rgb;
            if (type != 1) {
                *queue = enqueue(*queue, head->down_left);
            }
            *queue = dequeue(*queue);
            return root;
        }


    }
    return root;
}

void decompress(FILE* input, TQuadTree* root, char* buffer, int buffer_size) {
    RGB rgb;
    TQueue queue = NULL;
    for (int i = 0; i < buffer_size; i++) {
        unsigned char type = buffer[i];
        if (type == 0) {
            rgb.red = 0;
            rgb.green = 0;
            rgb.blue = 0;
            (*root) = insert(*root, type, rgb, &queue);
        } else if (type == 1) {
            rgb.red = buffer[++i];
            rgb.green = buffer[++i];
            rgb.blue = buffer[++i];
            (*root) = insert(*root, type, rgb, &queue);
        }
    }
    queue = free_queue(queue);
    free(buffer);
}

void free_tree(TQuadTree *tree) {
    if (*tree == NULL) {
        return;
    }
    free_tree(&(*tree)->up_left);
    free_tree(&(*tree)->up_right);
    free_tree(&(*tree)->down_right);
    free_tree(&(*tree)->down_left);
    free(*tree);
}
