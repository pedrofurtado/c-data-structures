/**
 * Static queue.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_MAX_NODES 5
#define QUEUE_EMPTY_POSITION -1

typedef int QUEUE_NODE_KEY;

typedef struct {
    char* info;
} QUEUE_NODE_DATA;

typedef struct {
    QUEUE_NODE_DATA data;
    QUEUE_NODE_KEY key;
} QUEUE_NODE;

typedef struct {
    QUEUE_NODE** nodes;
    int head;
    int tail;
} QUEUE;

QUEUE* init_queue();
void destroy_queue(QUEUE** queue);
bool enqueue(QUEUE* queue, QUEUE_NODE* queue_node);
QUEUE_NODE* dequeue(QUEUE* queue);
bool is_queue_empty(QUEUE* queue);
bool is_queue_full(QUEUE* queue);
int queue_size(QUEUE* queue);
QUEUE_NODE* create_queue_node(QUEUE_NODE_KEY key, char* info);
void print_queue(QUEUE* queue);
