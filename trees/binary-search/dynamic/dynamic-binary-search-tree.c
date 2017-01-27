/**
 * Dynamic binary search tree.
 */
#include "dynamic-binary-search-tree.h"

BINARY_SEARCH_TREE_NODE* init_binary_search_tree() {
    return NULL;
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
        aux = binary_search_tree_rightmost_node(&(*root)->left);
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
