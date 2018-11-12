#ifndef __TICK_H__
#define __TICK_H__

#define TICK_RATE_MILLISECONDS 5
#define TICKS_PER_SECOND 1000 / TICK_RATE_MILLISECONDS

#define TO_TICKS(x) (TICKS_PER_SECOND / (x))

#endif
