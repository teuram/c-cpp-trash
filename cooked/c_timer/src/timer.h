
#ifndef TIMER_H
#define TIMER_H

typedef struct {
    unsigned int cycle;
    unsigned int time;
} Timer;

int timer(Timer* timer);

#endif

