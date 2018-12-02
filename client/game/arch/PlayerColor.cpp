#include "PlayerColor.h"

namespace player_color {
    SdlColor *getColor(enum PlayerColor color) {
        switch (color) {
            case RED: {
                return new SdlColor(255, 153, 153);
            }
            case GREEN: {
                return new SdlColor(153, 255, 153);
            }
            case BLUE: {
                return new SdlColor(102, 178, 255);
            }
            case ORANGE: {
                return new SdlColor(255, 204, 153);
            }
            case YELLOW: {
                return new SdlColor(255, 255, 153);
            }
            default:
                return nullptr;
        }
    }
}
