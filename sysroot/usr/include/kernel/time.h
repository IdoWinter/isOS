#ifndef _KERNEL_TIME_H
#define _KERNEL_TIME_H


#define PIT_MAX_FREQUENCY 1193180
#define PIT_COMMAND_PORT 0x36
#define PIT_SET_FREQ 0x43
#define PIT_DATA_PORT 0x40

void timer_phase(int hz);

long time();

void handleTime();

void wait(long miliseconds);


#endif
