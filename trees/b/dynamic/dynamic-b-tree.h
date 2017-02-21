/**
 * Dynamic B tree.
 *
 * It's used the terminology of 'order' defined by Knuth, i.e., order as the maximum number of children pointers that every B tree node can have.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define B_TREE_ORDER 5

typedef int B_TREE_KEY;

typedef struct {
    char* info;
} B_TREE_DATA;

typedef struct B_TREE {
    bool leaf;
    int size;
    B_TREE_KEY* keys;
    B_TREE_DATA* data;
    struct B_TREE** pointers;
} B_TREE;

B_TREE* init_b_tree();
int b_tree_maximum_number_of_keys();
int b_tree_minimum_number_of_keys();
int b_tree_maximum_number_of_data();
int b_tree_minimum_number_of_data();
int b_tree_maximum_number_of_pointers();
int b_tree_minimum_number_of_pointers();
bool b_tree_is_full(B_TREE* root);
bool b_tree_is_empty(B_TREE* root);
B_TREE* b_tree_create_internal_node();
B_TREE* b_tree_create_leaf_node();
int b_tree_get_index(B_TREE* root, B_TREE_KEY key);
B_TREE_DATA* b_tree_search(B_TREE* root, B_TREE_KEY key);
void b_tree_split_child(B_TREE* x, int i, B_TREE* y);
bool b_tree_insert(B_TREE** root, B_TREE_KEY key, B_TREE_DATA data);
bool b_tree_insert_nonfull(B_TREE* x, B_TREE_KEY k, B_TREE_DATA data);
bool b_tree_delete(B_TREE** root, B_TREE_KEY key);
void destroy_b_tree(B_TREE** root);
void print_b_tree(B_TREE* p);
