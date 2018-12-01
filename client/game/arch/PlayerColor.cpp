#include "PlayerColor.h"

namespace player_color {
    SdlColor *getColor(enum PlayerColor color) {
        switch (color) {
            case RED: {
                return new SdlColor(255, 204, 204);
            }
            case GREEN: {
                return new SdlColor(204, 255, 204);
            }
            case BLUE: {
                return new SdlColor(204, 229, 255);
            }
            case ORANGE: {
                return new SdlColor(255, 229, 204);
            }
            case YELLOW: {
                return new SdlColor(255, 255, 204);
            }
            default:
                return nullptr;
        }
    }
}
