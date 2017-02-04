/**
 * Static max binary heap.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BINARY_HEAP_MAX_NODES 100
#define BINARY_HEAP_EMPTY_POSITION -1

typedef int BINARY_HEAP_NODE_KEY;
typedef int BINARY_HEAP_NODE_PRIORITY;

typedef struct {
    char* info;
} BINARY_HEAP_NODE_DATA;

typedef struct {
    BINARY_HEAP_NODE_KEY key;
    BINARY_HEAP_NODE_PRIORITY priority;
    BINARY_HEAP_NODE_DATA data;
} BINARY_HEAP_NODE;

typedef struct {
    BINARY_HEAP_NODE** nodes;
    int size;
} BINARY_HEAP;

BINARY_HEAP* init_binary_heap();
BINARY_HEAP_NODE* create_binary_heap_node(BINARY_HEAP_NODE_KEY key, BINARY_HEAP_NODE_PRIORITY priority, char* info);
bool is_binary_heap_empty(BINARY_HEAP* heap);
bool is_binary_heap_full(BINARY_HEAP* heap);
bool binary_heap_insert(BINARY_HEAP* heap, BINARY_HEAP_NODE* node);
void binary_heap_heapify_up(BINARY_HEAP* heap, int position);
BINARY_HEAP_NODE* binary_heap_extract(BINARY_HEAP* heap);
void binary_heap_heapify_down(BINARY_HEAP* heap, int position);
void print_binary_heap(BINARY_HEAP* heap, int position);
int binary_heap_parent(int position);
int binary_heap_left_child(int position);
int binary_heap_right_child(int position);
