/**
 * Static stack.
 */
#include "static-stack.h"

STACK* init_stack() {
    STACK* stack = (STACK*) malloc(sizeof(STACK));

    if(!stack) { return NULL; }

    stack->top = STACK_EMPTY_POSITION;
    stack->nodes = malloc(STACK_MAX_NODES * sizeof(STACK_NODE));

    int i;
    for(i = 0; i < STACK_MAX_NODES; i++) { stack->nodes[i] = NULL; }

    return stack;
}

STACK_NODE* create_stack_node(STACK_NODE_KEY key, char* info) {
    STACK_NODE* stack_node = (STACK_NODE*) malloc(sizeof(STACK_NODE));

    if(!stack_node) { return NULL; }

    stack_node->key = key;
    stack_node->data.info = info;

    return stack_node;
}

void destroy_stack(STACK** stack) {
    if(!*stack) { return; }

    while(!is_stack_empty(*stack)) { free(stack_pop(*stack)); }

    int i;
    for(i = 0; i < STACK_MAX_NODES; i++) { free((*stack)->nodes[i]); }

    free((*stack)->nodes);

    free(*stack);

    *stack = NULL;
}

bool stack_push(STACK* stack, STACK_NODE* stack_node) {
    if(!stack || !stack_node || is_stack_full(stack)) { return false; }

    stack->top++;
    stack->nodes[stack->top] = stack_node;

    return true;
}

STACK_NODE* stack_pop(STACK* stack) {
    if(!stack || is_stack_empty(stack)) { return NULL; }

    STACK_NODE* stack_node = stack->nodes[stack->top];

    stack->nodes[stack->top] = NULL;

    stack->top--;

    return stack_node;
}

bool is_stack_empty(STACK* stack) {
    return !stack || stack->top == STACK_EMPTY_POSITION;
}

bool is_stack_full(STACK* stack) {
    return stack && stack->top + 1 == STACK_MAX_NODES;
}

int stack_size(STACK* stack) {
    if(!stack || is_stack_empty(stack)) { return 0; }

    return stack->top + 1;
}

void print_stack(STACK* stack) {
    if(!stack) {
        printf("\nStack not initialized or destroyed.\n");
        return;
    }

    if(is_stack_empty(stack)) {
        printf("\nStack empty.\n");
        return;
    }

    printf("\nStack: [");

    int i;
    for(i = stack->top; i >= 0; i--) { printf("<%d, %s>, ", stack->nodes[i]->key, stack->nodes[i]->data.info); }

    printf("]. There are %d nodes in stack from a maximum number of %d nodes.\n", stack_size(stack), STACK_MAX_NODES);
}
