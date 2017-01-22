/**
 * Dynamic queue.
 */
#include "dynamic-queue.h"

QUEUE* init_queue() {
    QUEUE* queue = (QUEUE*) malloc(sizeof(QUEUE));

    if(!queue) { return NULL; }

    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

QUEUE_NODE* create_queue_node(QUEUE_NODE_KEY key, char* info) {
    QUEUE_NODE* queue_node = (QUEUE_NODE*) malloc(sizeof(QUEUE_NODE));

    if(!queue_node) { return NULL; }

    queue_node->key = key;
    queue_node->data.info = info;
    queue_node->next = NULL;

    return queue_node;
}

bool enqueue(QUEUE* queue, QUEUE_NODE* queue_node) {
    if(!queue || !queue_node) { return false; }

    if(queue->tail) {
        queue->tail->next = queue_node;
    }
    else {
        queue->head = queue_node;
    }

    queue->tail = queue_node;

    return true;
}

QUEUE_NODE* dequeue(QUEUE* queue) {
    if(!queue) { return NULL; }

    QUEUE_NODE* queue_node = queue->head;

    if(queue->head) {
        if(queue->head == queue->tail) { queue->tail = NULL; }
        queue->head = queue->head->next;
    }

    return queue_node;
}

void destroy_queue(QUEUE** queue) {
    if(!*queue) { return; }

    while(!is_queue_empty(*queue)) { free(dequeue(*queue)); }

    free(*queue);

    *queue = NULL;
}

bool is_queue_empty(QUEUE* queue) {
    return !queue || (!queue->head && !queue->tail);
}

int queue_size(QUEUE* queue) {
    if(!queue || is_queue_empty(queue)) { return 0; }

    int size = 0;

    QUEUE_NODE* q = queue->head;

    while(q) {
        size++;
        q = q->next;
    }

    return size;
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

    QUEUE_NODE* q = queue->head;

    printf("\nQueue: [");

    while(q) {
        printf("<%d, %s>, ", q->key, q->data.info);
        q = q->next;
    }

    printf("]. There are %d nodes in queue.\n", queue_size(queue));
}
