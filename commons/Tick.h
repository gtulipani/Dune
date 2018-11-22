#ifndef __TICK_H__
#define __TICK_H__

#include <chrono>

#define TICK_RATE 5

#define TICK_RATE_MILLISECONDS std::chrono::milliseconds(TICK_RATE)

#define TICKS_PER_SECOND 1000 / TICK_RATE
#define TO_TICKS(x) (TICKS_PER_SECOND / (x))

#endif
