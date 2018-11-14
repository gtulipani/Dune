#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// Commons Libraries
#include <Matrix.h>

// Client Libraries
#include "../sdl/SdlWindow.h"
#include "../sdl/SdlTexture.h"
#include "SdlPicturable.h"

typedef enum Movement {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Movement;

class MainWindow {
private:
    int width{};
    int height{};
    int rows_quantity{};
    int columns_quantity{};
    Matrix matrix;
    SdlWindow window{};
    SdlTexture terrain_texture;
    std::map<char, SdlTexture> terrains;
    std::map<char, SdlTexture> units;

    int offset_x{};
    int offset_y{};
    std::vector<SdlPicturable> picturables;

    void buildUnits();
    void buildTerrains();
public:
    MainWindow() = default;

    MainWindow(const MainWindow &other) = delete;

    // Overloading the assignment by copy
    MainWindow &operator=(const MainWindow &other) = delete;

    void configure(Matrix matrix);

    void fill();

    void preloadTerrainMatrix();

    void render();

    void move(enum Movement movement);

    void processPicturables(std::vector<Picturable> picturables);

    Point getRelativePoint(int row, int column);
};


#endif //__MAIN_WINDOW_H__
