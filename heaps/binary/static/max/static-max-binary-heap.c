/**
 * Static max binary heap.
 */
#include "static-max-binary-heap.h"

BINARY_HEAP* init_binary_heap() {
    BINARY_HEAP* heap = (BINARY_HEAP*) malloc(sizeof(BINARY_HEAP));

    if(!heap) { return NULL; }

    heap->nodes = malloc(BINARY_HEAP_MAX_NODES * sizeof(BINARY_HEAP_NODE));

    if(!heap->nodes) { return NULL; }

    int i;
    for(i = 0; i < BINARY_HEAP_MAX_NODES; i++) { heap->nodes[i] = NULL; }

    heap->size = BINARY_HEAP_EMPTY_POSITION;

    return heap;
}

bool binary_heap_insert(BINARY_HEAP* heap, BINARY_HEAP_NODE* node) {
    if(!heap || !node) { return false; }

    if(is_binary_heap_full(heap)) { return false; }

    heap->size++;
    heap->nodes[heap->size] = node;
    binary_heap_heapify_up(heap, heap->size);

    return true;
}

BINARY_HEAP_NODE* binary_heap_extract(BINARY_HEAP* heap) {
    if(!heap || is_binary_heap_empty(heap)) { return NULL; }

    BINARY_HEAP_NODE* node = heap->nodes[0];

    heap->nodes[0] = heap->nodes[heap->size];
    heap->nodes[heap->size] = NULL;
    heap->size--;

    if(!is_binary_heap_empty(heap)) { binary_heap_heapify_down(heap, 0); }

    return node;
}

void binary_heap_heapify_down(BINARY_HEAP* heap, int position) {
    if(!heap) { return; }

    int left_child = binary_heap_left_child(position);
    int right_child = binary_heap_right_child(position);
    int largest = position;

    if(left_child <= heap->size && heap->nodes[left_child]->priority > heap->nodes[largest]->priority) {
        largest = left_child;
    }

    if(right_child <= heap->size && heap->nodes[right_child]->priority > heap->nodes[largest]->priority) {
        largest = right_child;
    }

    if(largest != position) {
        BINARY_HEAP_NODE* aux = heap->nodes[position];
        heap->nodes[position] = heap->nodes[largest];
        heap->nodes[largest] = aux;

        binary_heap_heapify_down(heap, largest);
    }
}

int binary_heap_parent(int position) {
    return (position - 1) / 2;
}

int binary_heap_left_child(int position) {
    return (2 * position) + 1;
}

int binary_heap_right_child(int position) {
    return (2 * position) + 2;
}

void binary_heap_heapify_up(BINARY_HEAP* heap, int position) {
    if(!heap) { return; }

    int child = position;
    int parent = binary_heap_parent(child);

    BINARY_HEAP_NODE* aux;

    while(child > 0 && heap->nodes[child]->priority > heap->nodes[parent]->priority) {
        aux = heap->nodes[parent];
        heap->nodes[parent] = heap->nodes[child];
        heap->nodes[child] = aux;
        child = parent;
        parent = binary_heap_parent(child);
    }
}

bool is_binary_heap_empty(BINARY_HEAP* heap) {
    return !heap || heap->size == BINARY_HEAP_EMPTY_POSITION;
}

bool is_binary_heap_full(BINARY_HEAP* heap) {
    return heap && heap->size + 1 == BINARY_HEAP_MAX_NODES;
}

BINARY_HEAP_NODE* create_binary_heap_node(BINARY_HEAP_NODE_KEY key, BINARY_HEAP_NODE_PRIORITY priority, char* info) {
    BINARY_HEAP_NODE* node = (BINARY_HEAP_NODE*) malloc(sizeof(BINARY_HEAP_NODE));

    if(!node) { return NULL; }

    node->key = key;
    node->priority = priority;
    node->data.info = info;

    return node;
}

void print_binary_heap(BINARY_HEAP* heap, int position) {
    if(!heap || is_binary_heap_empty(heap)) {
        printf("--");
        return;
    }

    printf("%d", heap->nodes[position]->priority);

    int left_child = binary_heap_left_child(position);
    int right_child = binary_heap_right_child(position);

    if((heap->nodes[left_child] && left_child <= heap->size) || (heap->nodes[right_child] && right_child <= heap->size)) {
        printf("(");

        if(left_child <= heap->size) {
            print_binary_heap(heap, left_child);
        }
        else {
            printf("--");
        }

        printf(", ");

        if(right_child <= heap->size) {
            print_binary_heap(heap, right_child);
        }
        else {
            printf("--");
        }

        printf(")");
    }
}
