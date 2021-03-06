#ifndef __SCREEN_INFORMATION_H__
#define __SCREEN_INFORMATION_H__

// Commons libraries
#include <Point.h>

// General Screen configuration
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

// Terrain-panel rate
#define SCREEN_TERRAIN_RATE 0.75
#define SCREEN_BUTTONS_RATE 0.25

// Status and terrain sizes
#define SCREEN_TERRAIN_WIDTH int(SCREEN_WIDTH * SCREEN_TERRAIN_RATE)
#define SCREEN_STATUS_WIDTH SCREEN_TERRAIN_WIDTH

#define SCREEN_TERRAIN_HEIGHT int(SCREEN_HEIGHT - SCREEN_STATUS_HEIGHT)
#define SCREEN_STATUS_HEIGHT (SCREEN_HEIGHT / 30)

// Panel size
#define SCREEN_PANEL_WIDTH int(SCREEN_WIDTH * SCREEN_BUTTONS_RATE)
#define SCREEN_PANEL_HEIGHT int(SCREEN_HEIGHT)

// Eagle-eye position and size
#define EAGLE_EYE_X_OFFSET int(SCREEN_PANEL_WIDTH / 20)
#define EAGLE_EYE_Y_OFFSET int(SCREEN_HEIGHT / 30)

#define EAGLE_EYE_WIDTH int(SCREEN_PANEL_WIDTH - (2 * EAGLE_EYE_X_OFFSET))
#define EAGLE_EYE_HEIGHT int(SCREEN_HEIGHT * 2 / 5)

// Panel buttons position and size
#define PANEL_BUTTON_ICON_Y_OFFSET int(EAGLE_EYE_Y_OFFSET + EAGLE_EYE_HEIGHT + EAGLE_EYE_Y_OFFSET)
#define PANEL_BUTTON_ICON_X_OFFSET int(SCREEN_PANEL_WIDTH / 20)
#define PANEL_BUTTON_ICON_WIDTH int((SCREEN_PANEL_WIDTH - (2 * PANEL_BUTTON_ICON_X_OFFSET)) / 2)
#define PANEL_BUTTON_ICON_HEIGHT int(SCREEN_HEIGHT / 12)

#define PANEL_BUTTON_ICONS_ROWS_QUANTITY 6

typedef enum Movement {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Movement;

class ScreenInformation {
private:
    int offset_x;
    int offset_y;

public:
    ScreenInformation();

    int getOffsetX() const;
    int getOffsetY() const;

    void setOffsetX(int offset_x);
    void setOffsetY(int offset_y);

    Point getRelativePoint(int row, int column);
};


#endif //__SCREEN_INFORMATION_H__
