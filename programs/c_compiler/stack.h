
#ifndef _STACK_H_
#define _STACK_H_

#define MAX_ELEMENTS 8192

typedef struct stack {
    void* stack[MAX_ELEMENTS];
    int pointer;
} Stack;

void init_stack(Stack* stack);

void push(Stack* stack, const void* pointer);
void* pop(Stack* stack);

void* seek(Stack* stack);

#endif

