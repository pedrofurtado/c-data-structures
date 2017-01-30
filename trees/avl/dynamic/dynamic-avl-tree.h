/**
 * Dynamic AVL tree.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int AVL_TREE_NODE_KEY;

typedef struct {
    char* info;
} AVL_TREE_NODE_DATA;

typedef struct AVL_TREE_NODE {
    int height;
    AVL_TREE_NODE_DATA data;
    AVL_TREE_NODE_KEY key;
    struct AVL_TREE_NODE* left;
    struct AVL_TREE_NODE* right;
} AVL_TREE_NODE;

AVL_TREE_NODE* init_avl_tree();
void destroy_avl_tree(AVL_TREE_NODE** root);
int avl_tree_height(AVL_TREE_NODE* root);
int avl_tree_balance_factor(AVL_TREE_NODE* root);
int avl_tree_max(int a, int b);
int avl_tree_calculate_new_height(AVL_TREE_NODE* root);
bool avl_tree_insert(AVL_TREE_NODE** root, AVL_TREE_NODE* node);
AVL_TREE_NODE* create_avl_tree_node(AVL_TREE_NODE_KEY key, char* info);
AVL_TREE_NODE* avl_tree_search(AVL_TREE_NODE* root, AVL_TREE_NODE_KEY key);
bool avl_tree_delete(AVL_TREE_NODE** root, AVL_TREE_NODE_KEY key);
int avl_tree_size(AVL_TREE_NODE* root);
void print_avl_tree(AVL_TREE_NODE* root);
void avl_tree_pre_order(AVL_TREE_NODE* root);
void avl_tree_in_order(AVL_TREE_NODE* root);
void avl_tree_post_order(AVL_TREE_NODE* root);
void avl_tree_level_order(AVL_TREE_NODE* root);
void avl_tree_ll_rotation(AVL_TREE_NODE** root);
void avl_tree_rr_rotation(AVL_TREE_NODE** root);
void avl_tree_lr_rotation(AVL_TREE_NODE** root);
void avl_tree_rl_rotation(AVL_TREE_NODE** root);
