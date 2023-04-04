
#ifndef _LIST_H_
#define _LIST_H_

typedef struct list {
    void** list;
    int size;
    int elements;
} List;

List* init_list(int size);
void* list_get(List* self, int element);
void free_list(List* list, void (*free_fn)(void*));
void list_add(List* self, void* element);
void list_remove(List* self, int i);

#endif

