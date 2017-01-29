/**
 * Dynamic binary search tree.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int BINARY_SEARCH_TREE_NODE_KEY;

typedef struct {
    char* info;
} BINARY_SEARCH_TREE_DATA;

typedef struct BINARY_SEARCH_TREE_NODE {
    BINARY_SEARCH_TREE_DATA data;
    BINARY_SEARCH_TREE_NODE_KEY key;
    struct BINARY_SEARCH_TREE_NODE* left;
    struct BINARY_SEARCH_TREE_NODE* right;
} BINARY_SEARCH_TREE_NODE;

BINARY_SEARCH_TREE_NODE* init_binary_search_tree();
void destroy_binary_search_tree(BINARY_SEARCH_TREE_NODE** root);
BINARY_SEARCH_TREE_NODE* create_binary_search_tree_node(BINARY_SEARCH_TREE_NODE_KEY key, char* info);
bool binary_search_tree_insert(BINARY_SEARCH_TREE_NODE** root, BINARY_SEARCH_TREE_NODE* node);
BINARY_SEARCH_TREE_NODE* binary_search_tree_rightmost_node(BINARY_SEARCH_TREE_NODE* *root);
BINARY_SEARCH_TREE_NODE* binary_search_tree_leftmost_node(BINARY_SEARCH_TREE_NODE* *root);
bool binary_search_tree_delete(BINARY_SEARCH_TREE_NODE** root, BINARY_SEARCH_TREE_NODE_KEY key);
BINARY_SEARCH_TREE_NODE* binary_search_tree_search(BINARY_SEARCH_TREE_NODE* root, BINARY_SEARCH_TREE_NODE_KEY key);
void binary_search_tree_pre_order(BINARY_SEARCH_TREE_NODE* root);
void binary_search_tree_in_order(BINARY_SEARCH_TREE_NODE* root);
void binary_search_tree_post_order(BINARY_SEARCH_TREE_NODE* root);
void binary_search_tree_level_order(BINARY_SEARCH_TREE_NODE* root);
int binary_search_tree_size(BINARY_SEARCH_TREE_NODE* root);
void print_binary_search_tree(BINARY_SEARCH_TREE_NODE* root);
