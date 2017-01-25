/**
 * Dynamic stack.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int STACK_NODE_KEY;

typedef struct {
    char* info;
} STACK_NODE_DATA;

typedef struct STACK_NODE {
    STACK_NODE_DATA data;
    STACK_NODE_KEY key;
    struct STACK_NODE* next;
} STACK_NODE;

typedef struct {
    STACK_NODE* top;
} STACK;

STACK* init_stack();
void destroy_stack(STACK** stack);
bool stack_push(STACK* stack, STACK_NODE* stack_node);
STACK_NODE* stack_pop(STACK* stack);
bool is_stack_empty(STACK* stack);
int stack_size(STACK* stack);
STACK_NODE* create_stack_node(STACK_NODE_KEY key, char* info);
void print_stack(STACK* stack);
