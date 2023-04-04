#include <stdlib.h>

#include "stack.h"

void init_stack(Stack* stack) {
    if(stack == NULL) {
        stack = malloc(sizeof(Stack));

        if(stack == NULL) {
            printf("error: allocation error");
            exit(1);
        }
    }
    stack->pointer = 0;
    for(int i = 0; i < MAX_ELEMENTS; i++) {
        stack->stack[i] = NULL;
    }
}

void push(Stack* stack, const void* pointer) {
    if(stack == NULL) {
        init_stack(stack);
    }
    if(stack->pointer + 1 >= MAX_ELEMENTS) {
        printf("error: stack overflow");
        exit(5);
    }
    stack->stack[stack->pointer++] = (void*)pointer;
}

void* pop(Stack* stack) {
    if(stack == NULL) {
        printf("error: stack is null pointer");
        exit(6);
    }

    stack->pointer--;
    if(stack->pointer < 0) {
        printf("error: stack overflow");
        exit(7);
    }
    return stack->stack[stack->pointer];
}

void* seek(Stack* stack) {
    if(stack->pointer - 1 >= MAX_ELEMENTS) {
        printf("error: stack overflow");
        exit(1);
    }
    return stack->stack[stack->pointer - 1];
}

