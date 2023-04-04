
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stacknode.h"

StackNode* pushStackNode(StackNode* sn) {
    StackNode* t = (StackNode*)malloc(sizeof(StackNode));

    if (!t) {
        printf("error: memory allocation error\n");
        exit(1);
    }

    t->data = NULL;
    t->next = sn;

    return t;
}

StackNode* popStackNode(StackNode* sn) {
    if (!sn) return NULL;
    if (sn->data) {
        free(sn->data);
    }
    StackNode* t = sn->next;
    free(sn);
    return t;
}

void setStackNodeData(StackNode* sn, void* data, unsigned int size) {
    if (sn->data) {
        free(sn->data);
    }
    sn->data = malloc(size);

    if (!sn->data) {
        printf("error: memory allocation error\n");
        exit(1);
    }
    memcpy(sn->data, data, size);
}

void freeStack(StackNode* sn) {
    while (sn) {
        sn = popStackNode(sn);
    }
}

