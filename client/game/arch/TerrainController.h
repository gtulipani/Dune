#ifndef __TERRAIN_CONTROLLER_H__
#define __TERRAIN_CONTROLLER_H__

// Commons Libraries
#include <Matrix.h>
#include "../sdl/SdlWindow.h"
#include "../sdl/SdlTexture.h"
#include "SdlPicturable.h"

class SDL_MouseButtonEvent;
class EventsLooperThread;

typedef enum Movement {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Movement;

class TerrainController {
private:
    SdlWindow* window;
    ClientSpritesSupplier &client_sprites_supplier;

    int screen_width{};
    int screen_height{};

    int terrain_width_tiles{};
    int terrain_height_tiles{};

    int terrain_width{};
    int terrain_height{};

    Matrix matrix{};

    SdlTexture *terrain_texture;

    std::map<int, SdlTexture*> terrains_textures_map;
    std::map<int, SdlTexture*> picturables_textures_map;

    int offset_x{};
    int offset_y{};
    std::vector<SdlPicturable*> picturables;

    Point temporary_position{};

    SdlTexture *createTexture(const std::string& subpath, const std::string& file_path);
    SdlTexture *createPicturableTexture(const std::string& file_path);
    SdlTexture *createTerrainTexture(const std::string& file_path);

    void preloadTerrainMatrix();
    void buildUnits();
    void buildTerrains();
public:
    TerrainController(SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier);

    void configure(Matrix matrix, int window_width, int window_height);

    void fill();

    void render();

    void renderEagleEye(Area destiny);

    void processPicturables(std::vector<Picturable> picturables);

    Point getRelativePoint(int row, int column);

    void parseMouseClickButton(SDL_MouseButtonEvent &mouse_event);

    void parseMouseReleaseButton(SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer,
                                 std::function<void(EventsLooperThread *, std::string, Point, Point)> push_function);

    bool move(enum Movement movement);

    ~TerrainController();
};


#endif //__TERRAIN_CONTROLLER_H__
