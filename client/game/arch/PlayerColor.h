#ifndef __PLAYER_COLOR_H__
#define __PLAYER_COLOR_H__

#include "../sdl/SdlColor.h"

typedef enum PlayerColor {
    NO_PLAYER = -1,
    RED = 0,
    GREEN = 1,
    BLUE = 2,
    ORANGE = 3,
    YELLOW = 4
} PlayerColor;

namespace player_color {
    SdlColor *getColor(enum PlayerColor color);
}

#endif //__PLAYER_COLOR_H__
