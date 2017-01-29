/**
 * Dynamic binary search tree.
 */
#include "dynamic-binary-search-tree.h"
#include "dynamic-queue.h"

BINARY_SEARCH_TREE_NODE* init_binary_search_tree() {
    return NULL;
}

void destroy_binary_search_tree(BINARY_SEARCH_TREE_NODE** root) {
    if(!*root) { return; }

    destroy_binary_search_tree(&(*root)->left);
    destroy_binary_search_tree(&(*root)->right);

    free(*root);
    *root = NULL;
}

bool binary_search_tree_insert(BINARY_SEARCH_TREE_NODE** root, BINARY_SEARCH_TREE_NODE* node) {
    if(!node) { return false; }

    if(!*root) {
        *root = node;
        return true;
    }
    else if(node->key < (*root)->key) {
        return binary_search_tree_insert(&(*root)->left, node);
    }
    else if(node->key > (*root)->key) {
        return binary_search_tree_insert(&(*root)->right, node);
    }

    return false;
}

BINARY_SEARCH_TREE_NODE* create_binary_search_tree_node(BINARY_SEARCH_TREE_NODE_KEY key, char* info) {
    BINARY_SEARCH_TREE_NODE* node = (BINARY_SEARCH_TREE_NODE*) malloc(sizeof(BINARY_SEARCH_TREE_NODE));

    if(!node) { return NULL; }

    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->data.info = info;

    return node;
}

BINARY_SEARCH_TREE_NODE* binary_search_tree_search(BINARY_SEARCH_TREE_NODE* root, BINARY_SEARCH_TREE_NODE_KEY key) {
    if(!root) { return NULL; }

    if(key < root->key) {
        return binary_search_tree_search(root->left, key);
    }
    else if(key > root->key) {
        return binary_search_tree_search(root->right, key);
    }

    return root;
}

bool binary_search_tree_delete(BINARY_SEARCH_TREE_NODE** root, BINARY_SEARCH_TREE_NODE_KEY key) {
    if(!*root) { return false; }

    if(key < (*root)->key) {
        return binary_search_tree_delete(&(*root)->left, key);
    }
    else if(key > (*root)->key) {
        return binary_search_tree_delete(&(*root)->right, key);
    }

    BINARY_SEARCH_TREE_NODE* aux = NULL;

    if(!(*root)->left && !(*root)->right) {
        free(*root);
        *root = NULL;
    }
    else if((*root)->left && !(*root)->right) {
        aux = (*root)->left;
        free(*root);
        *root = aux;
    }
    else if(!(*root)->left && (*root)->right) {
        aux = (*root)->right;
        free(*root);
        *root = aux;
    }
    else {
        aux = binary_search_tree_rightmost_node(&(*root)->left); // OR aux = binary_search_tree_leftmost_node(&(*root)->right);
        aux->left = (*root)->left;
        aux->right = (*root)->right;
        free(*root);
        *root = aux;
    }

    return true;
}

BINARY_SEARCH_TREE_NODE* binary_search_tree_rightmost_node(BINARY_SEARCH_TREE_NODE* *root) {
    if((*root)->right) {
        return binary_search_tree_rightmost_node(&(*root)->right);
    }

    BINARY_SEARCH_TREE_NODE* aux = *root;

    *root = ((*root)->left) ? (*root)->left : NULL;

    return aux;
}

BINARY_SEARCH_TREE_NODE* binary_search_tree_leftmost_node(BINARY_SEARCH_TREE_NODE* *root) {
    if((*root)->left) {
        return binary_search_tree_leftmost_node(&(*root)->left);
    }

    BINARY_SEARCH_TREE_NODE* aux = *root;

    *root = ((*root)->right) ? (*root)->right : NULL;

    return aux;
}

int binary_search_tree_size(BINARY_SEARCH_TREE_NODE* root) {
    return (root) ? 1 + binary_search_tree_size(root->left) + binary_search_tree_size(root->right) : 0;
}

void print_binary_search_tree(BINARY_SEARCH_TREE_NODE* root) {
    if (root) {
        printf("%d", root->key);

        if (root->left || root->right) {
            printf("(");
            print_binary_search_tree(root->left);
            printf(", ");
            print_binary_search_tree(root->right);
            printf(")");
        }
    }
    else {
        printf("--");
    }
}

void binary_search_tree_pre_order(BINARY_SEARCH_TREE_NODE* root) {
    if(!root) { return; }

    printf("%d, ", root->key);
    binary_search_tree_pre_order(root->left);
    binary_search_tree_pre_order(root->right);
}

void binary_search_tree_in_order(BINARY_SEARCH_TREE_NODE* root) {
    if(!root) { return; }

    binary_search_tree_in_order(root->left);
    printf("%d, ", root->key);
    binary_search_tree_in_order(root->right);
}

void binary_search_tree_post_order(BINARY_SEARCH_TREE_NODE* root) {
    if(!root) { return; }

    binary_search_tree_post_order(root->left);
    binary_search_tree_post_order(root->right);
    printf("%d, ", root->key);
}

void binary_search_tree_level_order(BINARY_SEARCH_TREE_NODE* root) {
    if(!root) { return; }

    QUEUE* queue = init_queue();
    enqueue(queue, create_queue_node(root->key, root->data.info));

    QUEUE_NODE* queue_node;
    BINARY_SEARCH_TREE_NODE* tree_node;

    while(!is_queue_empty(queue)) {
        queue_node = dequeue(queue);
        tree_node = binary_search_tree_search(root, queue_node->key);

        printf("%d, ", tree_node->key);

        if(tree_node->left) { enqueue(queue, create_queue_node(tree_node->left->key, tree_node->left->data.info)); }

        if(tree_node->right) { enqueue(queue, create_queue_node(tree_node->right->key, tree_node->right->data.info)); }
    }

    destroy_queue(&queue);
}
