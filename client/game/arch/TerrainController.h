#ifndef __TERRAIN_CONTROLLER_H__
#define __TERRAIN_CONTROLLER_H__

// Commons Libraries
#include <Matrix.h>
#include "../sdl/SdlWindow.h"
#include "../sdl/SdlTexture.h"
#include "SdlPicturable.h"

typedef enum Movement {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Movement;

class TerrainController {
private:
    SdlWindow* window;

    int screen_width{};
    int screen_height{};

    int terrain_width_tiles{};
    int terrain_height_tiles{};


    int terrain_width{};
    int terrain_height{};

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

    void configure(Matrix matrix, int window_width, int window_height);

    void fill();

    void render();

    void processPicturables(std::vector<Picturable> picturables);

    Point getRelativePoint(int row, int column);

    bool move(enum Movement movement);
};


#endif //__TERRAIN_CONTROLLER_H__
