/**
 * Dynamic B tree.
 */
#include "dynamic-b-tree.h"

B_TREE* init_b_tree() {
    return NULL;
}

int b_tree_maximum_number_of_keys() {
    return B_TREE_ORDER - 1;
}

int b_tree_minimum_number_of_keys() {
    return (B_TREE_ORDER / 2) - 1;
}

int b_tree_maximum_number_of_data() {
    return b_tree_maximum_number_of_keys();
}

int b_tree_minimum_number_of_data() {
    return b_tree_minimum_number_of_keys();
}

int b_tree_maximum_number_of_pointers() {
    return B_TREE_ORDER;
}

int b_tree_minimum_number_of_pointers() {
    return B_TREE_ORDER / 2;
}

B_TREE* b_tree_create_internal_node() {
    B_TREE* b_tree_node = (B_TREE*) malloc(sizeof(B_TREE));

    if(!b_tree_node) { return NULL; }

    b_tree_node->keys = malloc(b_tree_maximum_number_of_keys() * sizeof(B_TREE_KEY));
    if(!b_tree_node->keys) { return NULL; }

    b_tree_node->data = malloc(b_tree_maximum_number_of_data() * sizeof(B_TREE_DATA));
    if(!b_tree_node->data) { return NULL; }

    b_tree_node->size = 0;
    b_tree_node->leaf = false;

    b_tree_node->pointers = malloc(b_tree_maximum_number_of_pointers() * sizeof(B_TREE));
    if(!b_tree_node->pointers) { return NULL; }

    int i;
    for(i = 0; i < b_tree_maximum_number_of_pointers(); i++) { b_tree_node->pointers[i] = NULL; }
    //for(i = 0; i < b_tree_maximum_number_of_data(); i++) { b_tree_node->data[i] = NULL; }

    return b_tree_node;
}

B_TREE* b_tree_create_leaf_node() {
    B_TREE* leaf_node = b_tree_create_internal_node();

    if(!leaf_node) { return NULL; }

    leaf_node->leaf = true;

    return leaf_node;
}

bool b_tree_is_full(B_TREE* root) {
    return (root) ? root->size == b_tree_maximum_number_of_keys() : false;
}

bool b_tree_is_empty(B_TREE* root) {
    return (root) ? root->size == 0 : true;
}

int b_tree_get_index(B_TREE* root, B_TREE_KEY key) {
    int i;
    for(i = 0; i < root->size && key > root->keys[i]; i++);
    return i;
}

void b_tree_split_child(B_TREE* x, int i, B_TREE* y) {
    B_TREE* z = b_tree_create_internal_node();
    z->leaf = y->leaf;
    z->size = b_tree_minimum_number_of_keys();

    int j;
    for(j = 0; j < b_tree_minimum_number_of_keys(); j++) {
        z->keys[j] = y->keys[j + b_tree_minimum_number_of_keys()];
        z->data[j] = y->data[j + b_tree_minimum_number_of_keys()];
    }

    if(!y->leaf) {
        for(j = 0; j < b_tree_minimum_number_of_pointers(); j++) {
            z->pointers[j] = y->pointers[j + b_tree_minimum_number_of_pointers()];
        }
    }

    y->size = b_tree_minimum_number_of_keys();

    for(j = x->size; j > i + 1; j--) {
        x->pointers[j] = x->pointers[j - 1];
    }

    x->pointers[i + 1] = z;

    for(j = x->size - 1; j > i; j--) {
        x->keys[j] = x->keys[j - 1];
        x->data[j] = x->data[j - 1];
    }

    x->keys[i] = y->keys[b_tree_minimum_number_of_pointers()];
    x->size++;
}

bool b_tree_insert(B_TREE** root, B_TREE_KEY key, B_TREE_DATA data) {
    if(!*root) {
        *root = b_tree_create_leaf_node();

        if(!*root) { return false; }

        (*root)->size++;
        (*root)->keys[0] = key;
        (*root)->data[0] = data;

        return true;
    }
    else if(b_tree_is_full(*root)) {
        B_TREE* s = b_tree_create_internal_node();
        s->pointers[0] = *root;
        *root = s;

        b_tree_split_child(s, 0, s->pointers[0]);
    }

    return b_tree_insert_nonfull(*root, key, data);
}

bool b_tree_insert_nonfull(B_TREE* x, B_TREE_KEY k, B_TREE_DATA data) {
    int i = x->size;

    if(x->leaf) {
        while(i >= 1 && k < x->keys[i]) {
            x->keys[i] = x->keys[i - 1];
            x->data[i] = x->data[i - 1];
            i--;
        }

        x->keys[i] = k;
        x->data[i] = data;
        x->size++;

        return true;
    }

    while(i >= 1 && k < x->keys[i]) {
        i--;
    }
    i++;

    if(b_tree_is_full(x->pointers[i])) {
        b_tree_split_child(x, i, x->pointers[i]);

        if(k > x->keys[i]) {
            i++;
        }
    }

    return b_tree_insert_nonfull(x->pointers[i], k, data);
}

void print_b_tree(B_TREE* p) {
    if (p) {
        if (p->leaf) {
            if (p->size > 0) {
                int i;
                for (i = 0; i < p->size - 1; i++) {
                    printf("%d ", p->keys[i]);
                }
                printf("%d", p->keys[p->size - 1]);
            }
        }
        else {
            if (p->size > 0) {
                int j;
                for (j = 0; j < p->size + 1; j++) {
                    printf("(");
                    print_b_tree(p->pointers[j]);
                    printf(")");
                    if (j < p->size) {
                        printf(" %d", p->keys[j]);
                        if (j + 1 < p->size + 1) {
                            printf(" ");
                        }
                    }
                }
            }
        }
    }
}

int main() {
    B_TREE* b_tree = init_b_tree();
    B_TREE_DATA* data = (B_TREE_DATA*) malloc(sizeof(B_TREE_DATA));
    data->info = "qq coisa";
    b_tree_insert(&b_tree, 5, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");
    b_tree_insert(&b_tree, 3, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");
    b_tree_insert(&b_tree, 4, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");
    b_tree_insert(&b_tree, 7, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");
    b_tree_insert(&b_tree, 8, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    printf("\n================================\n================================\n");

    return 0;
}
