#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

class Timer {
public:
    unsigned int cycle;
    unsigned int time;

    Timer(unsigned int cycle) {
        this->cycle = cycle;
    }

    int check() {
        if(utime() > time) {
            time = utime() + cycle;
            return 1;
        }
        return 0;
    }

    static unsigned int utime() {
        struct timeval time;
        gettimeofday(&time, NULL);
        unsigned int s1 = (time.tv_sec) * 1000;
        unsigned int s2 = (time.tv_usec / 1000);
        return s1 + s2;
    }
};

