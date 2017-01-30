/**
 * Dynamic AVL tree.
 */
#include "dynamic-avl-tree.h"
#include "dynamic-queue.h"

AVL_TREE_NODE* init_avl_tree() {
    return NULL;
}

void destroy_avl_tree(AVL_TREE_NODE** root) {
    if(!*root) { return; }

    destroy_avl_tree(&(*root)->left);
    destroy_avl_tree(&(*root)->right);

    free(*root);
    *root = NULL;
}

int avl_tree_height(AVL_TREE_NODE* root) {
    return (root) ? root->height : -1;
}

int avl_tree_balance_factor(AVL_TREE_NODE* root) {
    return (root) ? avl_tree_height(root->left) - avl_tree_height(root->right) : 0;
}

int avl_tree_max(int a, int b) {
    return (a > b) ? a : b;
}

int avl_tree_calculate_new_height(AVL_TREE_NODE* root) {
    if(!root) { return 0; }

    return avl_tree_max(avl_tree_height(root->left), avl_tree_height(root->right)) + 1;
}

bool avl_tree_insert(AVL_TREE_NODE** root, AVL_TREE_NODE* node) {
    if(!node) { return false; }

    if(!*root) {
        *root = node;
        return true;
    }
    else if(node->key < (*root)->key) {
        if (avl_tree_insert(&(*root)->left, node)) {
            if(avl_tree_balance_factor(*root) > 1) {
                if(node->key < (*root)->left->key) {
                    avl_tree_ll_rotation(root);
                }
                else {
                    avl_tree_lr_rotation(root);
                }
            }

            (*root)->height = avl_tree_calculate_new_height(*root);

            return true;
        }
    }
    else if(node->key > (*root)->key) {
        if(avl_tree_insert(&(*root)->right, node)) {
            if(avl_tree_balance_factor(*root) < -1) {
                if(node->key > (*root)->right->key) {
                    avl_tree_rr_rotation(root);
                }
                else {
                    avl_tree_rl_rotation(root);
                }
            }

            (*root)->height = avl_tree_calculate_new_height(*root);

            return true;
        }
    }

    return false;
}

AVL_TREE_NODE* create_avl_tree_node(AVL_TREE_NODE_KEY key, char* info) {
    AVL_TREE_NODE* node = (AVL_TREE_NODE*) malloc(sizeof(AVL_TREE_NODE));

    if(!node) { return NULL; }

    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->data.info = info;
    node->height = 0;

    return node;
}

AVL_TREE_NODE* avl_tree_search(AVL_TREE_NODE* root, AVL_TREE_NODE_KEY key) {
    if(!root) { return NULL; }

    if(key < root->key) {
        return avl_tree_search(root->left, key);
    }
    else if(key > root->key) {
        return avl_tree_search(root->right, key);
    }

    return root;
}

bool avl_tree_delete(AVL_TREE_NODE** root, AVL_TREE_NODE_KEY key) {
    return true;
}

int avl_tree_size(AVL_TREE_NODE* root) {
    return (root) ? 1 + avl_tree_size(root->left) + avl_tree_size(root->right) : 0;
}

void print_avl_tree(AVL_TREE_NODE* root) {
    if (root) {
        printf("%d", root->key);

        if (root->left || root->right) {
            printf("(");
            print_avl_tree(root->left);
            printf(", ");
            print_avl_tree(root->right);
            printf(")");
        }
    }
    else {
        printf("--");
    }
}

void avl_tree_pre_order(AVL_TREE_NODE* root) {
    if(!root) { return; }

    printf("%d, ", root->key);
    avl_tree_pre_order(root->left);
    avl_tree_pre_order(root->right);
}

void avl_tree_in_order(AVL_TREE_NODE* root) {
    if(!root) { return; }

    avl_tree_in_order(root->left);
    printf("%d, ", root->key);
    avl_tree_in_order(root->right);
}

void avl_tree_post_order(AVL_TREE_NODE* root) {
    if(!root) { return; }

    avl_tree_post_order(root->left);
    avl_tree_post_order(root->right);
    printf("%d, ", root->key);
}

void avl_tree_level_order(AVL_TREE_NODE* root) {
    if(!root) { return; }

    QUEUE* queue = init_queue();
    enqueue(queue, create_queue_node(root->key, root->data.info));

    QUEUE_NODE* queue_node;
    AVL_TREE_NODE* tree_node;

    while(!is_queue_empty(queue)) {
        queue_node = dequeue(queue);
        tree_node = avl_tree_search(root, queue_node->key);

        printf("%d, ", tree_node->key);

        if(tree_node->left) { enqueue(queue, create_queue_node(tree_node->left->key, tree_node->left->data.info)); }

        if(tree_node->right) { enqueue(queue, create_queue_node(tree_node->right->key, tree_node->right->data.info)); }
    }

    destroy_queue(&queue);
}

void avl_tree_rr_rotation(AVL_TREE_NODE** root) {
    if(!*root) { return; }

    AVL_TREE_NODE* aux = *root;
    *root = (*root)->right;
    aux->right = (*root)->left;
    (*root)->left = aux;

    aux->height = avl_tree_calculate_new_height(aux);
    (*root)->height = avl_tree_calculate_new_height(*root);
}

void avl_tree_ll_rotation(AVL_TREE_NODE** root) {
    if(!root) { return; }

    AVL_TREE_NODE* aux = *root;
    *root = (*root)->left;
    aux->left = (*root)->right;
    (*root)->right = aux;

    aux->height = avl_tree_calculate_new_height(aux);
    (*root)->height = avl_tree_calculate_new_height(*root);
}

void avl_tree_lr_rotation(AVL_TREE_NODE** root) {
    if(!*root) { return; }

    avl_tree_rr_rotation(&(*root)->left);
    avl_tree_ll_rotation(root);
}

void avl_tree_rl_rotation(AVL_TREE_NODE** root) {
    if(!*root) { return; }

    avl_tree_ll_rotation(&(*root)->right);
    avl_tree_rr_rotation(root);
}
