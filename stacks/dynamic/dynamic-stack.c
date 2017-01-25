/**
 * Dynamic stack.
 */
#include "dynamic-stack.h"

STACK* init_stack() {
    STACK* stack = (STACK*) malloc(sizeof(STACK));

    if(!stack) { return NULL; }

    stack->top = NULL;

    return stack;
}

STACK_NODE* create_stack_node(STACK_NODE_KEY key, char* info) {
    STACK_NODE* stack_node = (STACK_NODE*) malloc(sizeof(STACK_NODE));

    if(!stack_node) { return NULL; }

    stack_node->next = NULL;
    stack_node->key = key;
    stack_node->data.info = info;

    return stack_node;
}

bool stack_push(STACK* stack, STACK_NODE* stack_node) {
    if(!stack || !stack_node) { return false; }

    stack_node->next = stack->top;
    stack->top = stack_node;

    return true;
}

STACK_NODE* stack_pop(STACK* stack) {
    if(is_stack_empty(stack)) { return NULL; }

    STACK_NODE* stack_node = stack->top;

    stack->top = stack->top->next;

    return stack_node;
}

void destroy_stack(STACK** stack) {
    if(!*stack) { return; }

    while(!is_stack_empty(*stack)) { free(stack_pop(*stack)); }

    free(*stack);

    *stack = NULL;
}

bool is_stack_empty(STACK* stack) {
    return !stack || !stack->top;
}

int stack_size(STACK* stack) {
    if(is_stack_empty(stack)) { return 0; }

    int size = 0;

    STACK_NODE* s = stack->top;

    while(s) {
        size++;
        s = s->next;
    }

    return size;
}

void print_stack(STACK* stack) {
    if(!stack) {
        printf("\nStack not initialized or destroyed.\n");
        return;
    }

    if(is_stack_empty(stack)) {
        printf("\nEmpty stack.\n");
        return;
    }

    printf("\nStack: [");

    STACK_NODE* stack_node = stack->top;

    while(stack_node) {
        printf("<%d, %s>, ", stack_node->key, stack_node->data.info);
        stack_node = stack_node->next;
    }

    printf("]. There are %d nodes in stack.\n", stack_size(stack));
}
