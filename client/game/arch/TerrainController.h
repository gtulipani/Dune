#ifndef __TERRAIN_CONTROLLER_H__
#define __TERRAIN_CONTROLLER_H__

// Commons Libraries
#include <Matrix.h>
#include "../sdl/SdlWindow.h"
#include "../sdl/SdlTexture.h"
#include "SdlPicturable.h"

#define MAIN_WINDOW_RESOLUTION_WIDTH 800
#define MAIN_WINDOW_RESOLUTION_HEIGHT 600

typedef enum Movement {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Movement;

class TerrainController {
private:
    int width{};
    int height{};
    int rows_quantity{};
    int columns_quantity{};
    SdlWindow* window;
    Matrix matrix{};


    SdlTexture terrain_texture{};

    std::map<char, SdlTexture> terrains{};
    std::map<char, SdlTexture> units{};

    int offset_x{};
    int offset_y{};
    std::vector<SdlPicturable> picturables{};

    void preloadTerrainMatrix();
    void buildUnits();
    void buildTerrains();
public:
    explicit TerrainController(SdlWindow *window);

    void configure(Matrix matrix);

    void fill();

    void render();

    void processPicturables(std::vector<Picturable> picturables);

    Point getRelativePoint(int row, int column);

    void move(enum Movement movement);
};


#endif //__TERRAIN_CONTROLLER_H__
