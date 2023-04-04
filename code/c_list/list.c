
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

static void resize_list(List* self, int size) {
    void** list = (void**)realloc(self->list, size);

    if(list == NULL) {
        printf("list: memory allocation error\nfrom %s", __func__);
        exit(-1);
    }

    self->size = size;
    self->list = list;
}

List* init_list(int size) {
    List* list = (List*)malloc(sizeof(List));

    if(list == NULL) {
        printf("list: memory allocation error\nfrom %s", __func__);
        exit(-1);
    }

    resize_list(list, size);
    list->elements = 0;

    return list;
}

void* list_get(List* self, int element) {
    return *(self->list + element);
}

void list_add(List* self, void* element) {

    if(self->elements == self->size) {
        resize_list(self, (self->size * 3) / 2 + 1);
    }

    self->list[self->elements++] = element;
}

void list_remove(List* self, int i) {
    for(int j = i; j < self->elements; j++) {
        *(self->list + j) = *(self->list + j + 1);
    }
    self->elements--;
}

void free_list(List* list, void (*free_fn)(void*)) {
    if(free_fn != NULL) {
        for(int i = 0; i < list->elements; i++) {
            free_fn(list_get(list, i));
        }
    }
    free(list->list);
    free(list);
}

