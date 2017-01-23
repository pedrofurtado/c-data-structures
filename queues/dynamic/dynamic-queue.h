/**
 * Dynamic Queue.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int QUEUE_NODE_KEY;

typedef struct {
    char* info;
} QUEUE_NODE_DATA;

typedef struct QUEUE_NODE {
    QUEUE_NODE_DATA data;
    QUEUE_NODE_KEY key;
    struct QUEUE_NODE* next;
} QUEUE_NODE;

typedef struct {
    QUEUE_NODE* head;
    QUEUE_NODE* tail;
} QUEUE;

QUEUE* init_queue();
void destroy_queue(QUEUE** queue);
bool enqueue(QUEUE* queue, QUEUE_NODE* queue_node);
QUEUE_NODE* dequeue(QUEUE* queue);
bool is_queue_empty(QUEUE* queue);
int queue_size(QUEUE* queue);
QUEUE_NODE* create_queue_node(QUEUE_NODE_KEY key, char* info);
void print_queue(QUEUE* queue);
