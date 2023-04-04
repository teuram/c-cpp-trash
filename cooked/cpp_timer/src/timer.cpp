
#ifndef TIMER_CPP
#define TIMER_CPP

#include <sys/types.h>
#include <sys/time.h>

#include "timer.h"

class Timer {
public:
    time_t cycle;
    time_t time;

    Timer(time_t cycle) {
        this->cycle = cycle;
    }

    int check() {
        if(utime() > time) {
            time = utime() + cycle;
            return 1;
        }
        return 0;
    }

    static time_t utime() {
        struct timeval time;
        gettimeofday(&time, NULL);
        time_t s1 = (time.tv_sec) * 1000;
        time_t s2 = (time.tv_usec / 1000);
        return s1 + s2;
    }
};

#endif

