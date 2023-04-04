#include <stdio.h>

#include "timer.h"

int main() {

    int count = 0;
    Timer t;
    t.cycle = 1000 / 20;

    while(1) {
        if(timer(&t)) {
            printf("count: %d\r", count);
            fflush(stdout);
            count++;
        }
    }

    return 0;
}

