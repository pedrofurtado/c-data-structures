/**
 * Dynamic B tree.
 */
#include "dynamic-b-tree.h"

B_TREE* init_b_tree() {
    return NULL;
}

int b_tree_maximum_number_of_keys() {
    return (2 * B_TREE_ORDER) - 1;
}

int b_tree_minimum_number_of_keys() {
    return B_TREE_ORDER - 1;
}

int b_tree_maximum_number_of_data() {
    return b_tree_maximum_number_of_keys();
}

int b_tree_minimum_number_of_data() {
    return b_tree_minimum_number_of_keys();
}

int b_tree_maximum_number_of_pointers() {
    return 2 * B_TREE_ORDER;
}

int b_tree_minimum_number_of_pointers() {
    return B_TREE_ORDER;
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

void b_tree_split_child(B_TREE* x, int i, B_TREE* y) {
    B_TREE* z = b_tree_create_internal_node();
    z->leaf = y->leaf;
    z->size = b_tree_minimum_number_of_keys();

    int j;
    for(j = 0; j < b_tree_minimum_number_of_keys(); j++) {
        z->keys[j] = y->keys[j + b_tree_minimum_number_of_pointers()];
        z->data[j] = y->data[j + b_tree_minimum_number_of_pointers()];
    }

    if(!y->leaf) {
        for(j = 0; j < b_tree_minimum_number_of_pointers(); j++) {
            z->pointers[j] = y->pointers[j + b_tree_minimum_number_of_pointers()];
        }
    }

    y->size = b_tree_minimum_number_of_keys();

    for (j = x->size; j >= i + 1; j--) {
        x->pointers[j + 1] = x->pointers[j];
    }

    x->pointers[i + 1] = z;

    for (j = x->size - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
        x->data[j + 1] = x->data[j];
    }

    x->keys[i] = y->keys[b_tree_minimum_number_of_keys()];
    x->data[i] = y->data[b_tree_minimum_number_of_keys()];

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

        if(!s) { return false; }

        s->pointers[0] = *root;

        b_tree_split_child(s, 0, *root);

        *root = s;

        int i = 0;
        if (s->keys[0] < key) { i++; }

        return b_tree_insert_nonfull(s->pointers[i], key, data);
    }

    return b_tree_insert_nonfull(*root, key, data);
}

bool b_tree_insert_nonfull(B_TREE* x, B_TREE_KEY k, B_TREE_DATA data) {
    int i = x->size - 1;

    if(x->leaf) {
        while (i >= 0 && x->keys[i] > k) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }

        x->keys[i + 1] = k;
        x->data[i + 1] = data;
        x->size++;

        return true;
    }

    while (i >= 0 && x->keys[i] > k) {
        i--;
    }

    if (b_tree_is_full(x->pointers[i + 1])) {
        b_tree_split_child(x, i + 1, x->pointers[i + 1]);

        if (x->keys[i + 1] < k) {
            i++;
        }
    }

    return b_tree_insert_nonfull(x->pointers[i + 1], k, data);
}

int b_tree_find_key(B_TREE* x, B_TREE_KEY k) {
    int idx = 0;

    while (idx < x->size && x->keys[idx] < k) {
        idx++;
    }

    return idx;
}

B_TREE_KEY b_tree_get_predecessor(B_TREE* x, int idx) {
    // Keep moving to the right most node until we reach a leaf
    B_TREE* cur = x->pointers[idx];

    while (!cur->leaf) {
        cur = cur->pointers[cur->size];
    }

    // Return the last key of the leaf
    return cur->keys[cur->size - 1];
}

B_TREE_KEY b_tree_get_successor(B_TREE* x, int idx) {
    // Keep moving the left most node starting from C[idx+1] until we reach a leaf
    B_TREE* cur = x->pointers[idx + 1];

    while (!cur->leaf) {
        cur = cur->pointers[0];
    }

    // Return the first key of the leaf
    return cur->keys[0];
}

void b_tree_destroy_node(B_TREE* x) {
    if(!x) { return; }

    free(x->keys);
    free(x->data);
    free(x->pointers);
    free(x);
}

void b_tree_merge(B_TREE* x, int idx) {
    B_TREE* child = x->pointers[idx];
    B_TREE* sibling = x->pointers[idx + 1];

    // Pulling a key from the current node and inserting it into (t-1)th
    // position of C[idx]
    child->keys[b_tree_minimum_number_of_keys()] = x->keys[idx];

    // Copying the keys from C[idx+1] to C[idx] at the end
    int i;
    for (i = 0; i < sibling->size; i++) {
        child->keys[i + b_tree_minimum_number_of_pointers()] = sibling->keys[i];
    }

    // Copying the child pointers from C[idx+1] to C[idx]
    if (!child->leaf) {
        for(i = 0; i <= sibling->size; i++) {
            child->pointers[i + b_tree_minimum_number_of_pointers()] = sibling->pointers[i];
        }
    }

    // Moving all keys after idx in the current node one step before -
    // to fill the gap created by moving keys[idx] to C[idx]
    for (i = idx + 1; i < x->size; i++) {
        x->keys[i - 1] = x->keys[i];
    }

    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for (i = idx + 2; i <= x->size; i++) {
        x->pointers[i - 1] = x->pointers[i];
    }

    // Updating the key count of child and the current node
    child->size += sibling->size + 1;
    x->size--;

    // Freeing the memory occupied by sibling
    b_tree_destroy_node(sibling);
}

void b_tree_delete_from_non_leaf(B_TREE* x, int idx) {
    int k = x->keys[idx];

    // If the child that precedes k (C[idx]) has atleast t keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // C[idx]. Replace k by pred. Recursively delete pred
    // in C[idx]
    if (x->pointers[idx]->size >= b_tree_minimum_number_of_pointers()) {
        B_TREE_KEY pred = b_tree_get_predecessor(x, idx);
        x->keys[idx] = pred;
        b_tree_delete(x->pointers[idx], pred);
    }

    // If the child C[idx] has less that t keys, examine C[idx+1].
    // If C[idx+1] has atleast t keys, find the successor 'succ' of k in
    // the subtree rooted at C[idx+1]
    // Replace k by succ
    // Recursively delete succ in C[idx+1]
    else if (x->pointers[idx + 1]->size >= b_tree_minimum_number_of_pointers()) {
        B_TREE_KEY succ = b_tree_get_successor(x, idx);
        x->keys[idx] = succ;
        b_tree_delete(x->pointers[idx + 1], succ);
    }

    // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1]
    // into C[idx]
    // Now C[idx] contains 2t-1 keys
    // Free C[idx+1] and recursively delete k from C[idx]
    else {
        b_tree_merge(x, idx);
        b_tree_delete(x->pointers[idx], k);
    }
}

void b_tree_delete_from_leaf(B_TREE* x, int idx) {
    // Move all the keys after the idx-th pos one place backward
    int i;
    for (i = idx + 1; i < x->size; i++) {
        x->keys[i - 1] = x->keys[i];
    }

    // Reduce the count of keys
    x->size--;
}

void b_tree_borrow_from_previous(B_TREE* x, int idx) {
    B_TREE* child = x->pointers[idx];
    B_TREE* sibling = x->pointers[idx - 1];

    // The last key from C[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in C[idx]. Thus, the  loses
    // sibling one key and child gains one key

    // Moving all key in C[idx] one step ahead
    int i;
    for (i = child->size - 1; i >= 0; i--) {
        child->keys[i + 1] = child->keys[i];
    }

    // If C[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->leaf) {
        for(i = child->size; i >= 0; i--) {
            child->pointers[i + 1] = child->pointers[i];
        }
    }

    // Setting child's first key equal to keys[idx-1] from the current node
    child->keys[0] = x->keys[idx - 1];

    // Moving sibling's last child as C[idx]'s first child
    if (!x->leaf) {
        child->pointers[0] = sibling->pointers[sibling->size];
    }

    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    x->keys[idx - 1] = sibling->keys[sibling->size - 1];

    child->size++;
    sibling->size--;
}

void b_tree_borrow_from_next(B_TREE* x, int idx) {
    B_TREE* child = x->pointers[idx];
    B_TREE* sibling = x->pointers[idx + 1];

    // keys[idx] is inserted as the last key in C[idx]
    child->keys[child->size] = x->keys[idx];

    // Sibling's first child is inserted as the last child
    // into C[idx]
    if (!child->leaf) {
        child->pointers[child->size + 1] = sibling->pointers[0];
    }

    //The first key from sibling is inserted into keys[idx]
    x->keys[idx] = sibling->keys[0];

    // Moving all keys in sibling one step behind
    int i;
    for (i = 1; i < sibling->size; i++) {
        sibling->keys[i - 1] = sibling->keys[i];
    }

    // Moving the child pointers one step behind
    if (!sibling->leaf) {
        for(i = 1; i <= sibling->size; i++) {
            sibling->pointers[i - 1] = sibling->pointers[i];
        }
    }

    // Increasing and decreasing the key count of C[idx] and C[idx+1]
    // respectively
    child->size++;
    sibling->size--;
}

void b_tree_fill(B_TREE* x, int idx) {
    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
    // from that child
    if (idx != 0 && x->pointers[idx - 1]->size >= b_tree_minimum_number_of_pointers()) {
        b_tree_borrow_from_previous(x, idx);
    }

    // If the next child(C[idx+1]) has more than t-1 keys, borrow a key
    // from that child
    else if (idx != x->size && x->pointers[idx + 1]->size >= b_tree_minimum_number_of_pointers()) {
        b_tree_borrow_from_next(x, idx);
    }

    // Merge C[idx] with its sibling
    // If C[idx] is the last child, merge it with with its previous sibling
    // Otherwise merge it with its next sibling
    else if (idx != x->size) {
        b_tree_merge(x, idx);
    }
    else {
        b_tree_merge(x, idx - 1);
    }
}

bool b_tree_delete(B_TREE* x, B_TREE_KEY k) {
    int idx = b_tree_find_key(x, k);

    // The key to be removed is present in this node
    if (idx < x->size && x->keys[idx] == k) {
        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (x->leaf) {
            b_tree_delete_from_leaf(x, idx);
        }
        else {
            b_tree_delete_from_non_leaf(x, idx);
        }

        return true;
    }

    // If this node is a leaf node, then the key is not present in tree
    if (x->leaf) {
        //The key "k" is does not exist in the tree\n";
        return false;
    }

    // The key to be removed is present in the sub-tree rooted with this node
    // The flag indicates whether the key is present in the sub-tree rooted
    // with the last child of this node
    bool flag = (idx == x->size);

    // If the child where the key is supposed to exist has less that t keys,
    // we fill that child
    if (x->pointers[idx]->size < b_tree_minimum_number_of_pointers()) {
        b_tree_fill(x, idx);
    }

    // If the last child has been merged, it must have merged with the previous
    // child and so we recurse on the (idx-1)th child. Else, we recurse on the
    // (idx)th child which now has atleast t keys
    if (flag && idx > x->size) {
        return b_tree_delete(x->pointers[idx - 1], k);
    }

    return b_tree_delete(x->pointers[idx], k);
}

bool b_tree_delete_from_root(B_TREE** root, B_TREE_KEY k) {
    if (!*root) { return false; }

    if(!b_tree_delete(*root, k)) { return false; }

    // If the root node has 0 keys, make its first child as the new root
    //  if it has a child, otherwise set root as NULL
    if ((*root)->size == 0) {
        B_TREE* tmp = *root;

        if ((*root)->leaf) {
            *root = NULL;
        }
        else {
            *root = (*root)->pointers[0];
        }

        // Free the old root
        b_tree_destroy_node(tmp);
    }

    return true;
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

    b_tree_insert(&b_tree, 6, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 2, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 4, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 9, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 1, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 0, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 0, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 10, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 41, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 15, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 16, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 17, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 35, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 9, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 1, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 0, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 42, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    b_tree_insert(&b_tree, 43, *data);
    printf("\n"); print_b_tree(b_tree); printf("\n");

    printf("\n================================\n================================\n");
    B_TREE_KEY k;

    k = 5;
    if(b_tree_delete_from_root(&b_tree, k)) { printf("\n REmovido a chave %d\n", k); print_b_tree(b_tree); printf("\n"); } else { printf("\n Nao foi encontrado a chave %d\n", k); }

    k = 5;
    if(b_tree_delete_from_root(&b_tree, k)) { printf("\n REmovido a chave %d\n", k); print_b_tree(b_tree); printf("\n"); } else { printf("\n Nao foi encontrado a chave %d\n", k); }

    k = 5;
    if(b_tree_delete_from_root(&b_tree, k)) { printf("\n REmovido a chave %d\n", k); print_b_tree(b_tree); printf("\n"); } else { printf("\n Nao foi encontrado a chave %d\n", k); }

    k = 5;
    if(b_tree_delete_from_root(&b_tree, k)) { printf("\n REmovido a chave %d\n", k); print_b_tree(b_tree); printf("\n"); } else { printf("\n Nao foi encontrado a chave %d\n", k); }

    k = 5;
    if(b_tree_delete_from_root(&b_tree, k)) { printf("\n REmovido a chave %d\n", k); print_b_tree(b_tree); printf("\n"); } else { printf("\n Nao foi encontrado a chave %d\n", k); }

    k = 5;
    if(b_tree_delete_from_root(&b_tree, k)) { printf("\n REmovido a chave %d\n", k); print_b_tree(b_tree); printf("\n"); } else { printf("\n Nao foi encontrado a chave %d\n", k); }

    k = 5;
    if(b_tree_delete_from_root(&b_tree, k)) { printf("\n REmovido a chave %d\n", k); print_b_tree(b_tree); printf("\n"); } else { printf("\n Nao foi encontrado a chave %d\n", k); }

    k = 5;
    if(b_tree_delete_from_root(&b_tree, k)) { printf("\n REmovido a chave %d\n", k); print_b_tree(b_tree); printf("\n"); } else { printf("\n Nao foi encontrado a chave %d\n", k); }

    k = 5;
    if(b_tree_delete_from_root(&b_tree, k)) { printf("\n REmovido a chave %d\n", k); print_b_tree(b_tree); printf("\n"); } else { printf("\n Nao foi encontrado a chave %d\n", k); }

    k = 5;
    if(b_tree_delete_from_root(&b_tree, k)) { printf("\n REmovido a chave %d\n", k); print_b_tree(b_tree); printf("\n"); } else { printf("\n Nao foi encontrado a chave %d\n", k); }

    return 0;
}
