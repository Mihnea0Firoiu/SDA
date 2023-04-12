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
    
    up_left = height(root->up_left) + 1;
    up_right = height(root->up_right) + 1;
    down_right = height(root->down_right) + 1;
    down_left = height(root->down_left) + 1;

    if (up_left <= up_right && up_left <= down_left && up_left <= down_right) {
        return up_left;
    } else if (up_right <= up_left && up_right <= down_left
     && up_right <= down_right) {
        return up_right;
    } else if (down_left <= up_left && down_left <= up_right
     && down_left <= down_right) {
        return down_left;
    } else if (down_right <= up_left && down_right <= up_right
     && down_right <= down_left) {
        return down_right;
    }
    return 0;
}
