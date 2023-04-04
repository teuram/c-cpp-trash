
#ifndef CHANK_CPP
#define CHANK_CPP

#include <stdlib.h>

template<typename T>
class Chank {
private:
    size_t size;
    T* obj;

public:

    Chank(size_t size) {
        this->size = size;
        obj = (T*)malloc(size * size * sizeof(T));
    }

    T* get(int x, int y) {
        return obj[(y % size) * size + (x % size)];
    }

    void fn(void (*fn)(T* t)) {
        for (size_t i = 0; i < size * size; i++) {
            fn(obj[i]);
        }
    }

    ~Chank() {
        free(obj);
    }
};

#endif

