/**
 * Static queue.
 */
#include "static-queue.h"

QUEUE* init_queue() {
    QUEUE* queue = (QUEUE*) malloc(sizeof(QUEUE));

    if(!queue) { return NULL; }

    queue->nodes = malloc(QUEUE_MAX_NODES * sizeof(QUEUE_NODE));

    if(!queue->nodes) { return NULL; }

    int i;
    for(i = 0; i < QUEUE_MAX_NODES; i++) { queue->nodes[i] = NULL; }

    queue->head = QUEUE_EMPTY_POSITION;
    queue->tail = QUEUE_EMPTY_POSITION;

    return queue;
}

bool enqueue(QUEUE* queue, QUEUE_NODE* queue_node) {
    if(!queue || !queue_node) { return false; }

    if(is_queue_full(queue)) { return false; }

    if(is_queue_empty(queue)) { queue->head = 0; }

    queue->tail = (queue->tail + 1) % QUEUE_MAX_NODES;
    queue->nodes[queue->tail] = queue_node;

    return true;
}

QUEUE_NODE* dequeue(QUEUE* queue) {
    if(!queue) { return NULL; }

    if(is_queue_empty(queue)) { return NULL; }

    QUEUE_NODE* queue_node = queue->nodes[queue->head];

    queue->nodes[queue->head] = NULL;

    if(queue->head == queue->tail) {
        queue->head = QUEUE_EMPTY_POSITION;
        queue->tail = QUEUE_EMPTY_POSITION;
    }
    else {
        queue->head = (queue->head + 1) % QUEUE_MAX_NODES;
    }

    return queue_node;
}

QUEUE_NODE* create_queue_node(QUEUE_NODE_KEY key, char* info) {
    QUEUE_NODE* queue_node = (QUEUE_NODE*) malloc(sizeof(QUEUE_NODE));

    if(!queue_node) { return NULL; }

    queue_node->key = key;
    queue_node->data.info = info;

    return queue_node;
}

bool is_queue_empty(QUEUE* queue) {
    return !queue || (queue->head == QUEUE_EMPTY_POSITION && queue->tail == QUEUE_EMPTY_POSITION);
}

bool is_queue_full(QUEUE* queue) {
    return queue && ((queue->tail + 1) % QUEUE_MAX_NODES) == queue->head;
}

int queue_size(QUEUE* queue) {
    if(!queue || is_queue_empty(queue)) { return 0; }

    return (queue->head > queue->tail) ? (QUEUE_MAX_NODES - queue->head + queue->tail + 1) : (queue->tail - queue->head + 1);
}

void destroy_queue(QUEUE** queue) {
    if(!*queue) { return; }

    while(!is_queue_empty(*queue)) { free(dequeue(*queue)); }

    int i;
    for(i = 0; i < QUEUE_MAX_NODES; i++) { free((*queue)->nodes[i]); }

    free((*queue)->nodes);

    free(*queue);

    *queue = NULL;
}

void print_queue(QUEUE* queue) {
    if(!queue) {
        printf("\nQueue not initialized or destroyed.\n");
        return;
    }

    if(is_queue_empty(queue)) {
        printf("\nQueue empty.\n");
        return;
    }

    printf("\nQueue: [");

    int i;
    int j = 0;
    for(i = queue->head; j < queue_size(queue); i = (i + 1) % QUEUE_MAX_NODES) {
        printf("<%d, %s>, ", queue->nodes[i]->key, queue->nodes[i]->data.info);
        j++;
    }

    printf("]. There are %d nodes in queue from a maximum number of %d nodes.\n", queue_size(queue), QUEUE_MAX_NODES);
}
