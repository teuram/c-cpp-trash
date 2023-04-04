
#ifndef STACKNODE_H
#define STACKNODE_H

typedef struct StackNode {
    void* data;
    struct StackNode* next;
} StackNode;

StackNode* pushStackNode(StackNode* sn);
StackNode* popStackNode(StackNode* sn);
void setStackNodeData(StackNode* sn, void* data, unsigned int size);
void freeStack(StackNode* sn);

#endif

