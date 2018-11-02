#include "Event.h"

Event::Event(string type, Point& src, Point& dst) : type(move(type)), src(src), dst(dst) {}
