#ifndef __TERRAIN_CONTROLLER_H__
#define __TERRAIN_CONTROLLER_H__

// Commons Libraries
#include <Matrix.h>
#include "../../sdl/SdlWindow.h"
#include "../../sdl/SdlTexture.h"
#include "../SdlPicturable.h"

#include "Controller.h"

struct SDL_MouseButtonEvent;
class EventsLooperThread;

class TerrainController : public Controller {
private:
    ClientSpritesSupplier &client_sprites_supplier;
    Matrix matrix;
    int terrain_width_tiles;
    int terrain_height_tiles;
    int terrain_width;
    int terrain_height;
    bool clicked;
    std::map<int, SdlTexture*> terrains_textures_map;
    std::map<std::string, std::map<int, std::map<int, SdlTexture*>>> picturables_map;
    SdlTexture *terrain_texture;

    int offset_x{};
    int offset_y{};
    std::vector<SdlPicturable*> picturables;

    Point temporary_position{};

    void renderEagleEye();

    void buildTerrains();
    void buildUnits();
    void buildTerrainTexture();
    void preloadTerrainMatrix();

    SdlTexture *createTexture(const std::string& subpath, const std::string& file_path);
    SdlTexture *createPicturableTexture(const std::string& file_path);
    SdlTexture *createTerrainTexture(const std::string& file_path);
public:
    TerrainController(SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier, const ScreenConfiguration& screen_configuration, const Matrix& matrix);

    void update(const GameStatusEvent &event) override;

    void render() override;

    void move(enum Movement movement) override;

    bool resolvePendingAction(const SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer, const std::function<void(EventsLooperThread *, int, int, Point, Point)>& push_function) override;
    void parseMouseClick(const SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, const std::function<void(EventsLooperThread*, int, int, Point, Point)>& push_function) override;
    void parseMouseRelease(const SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer, const std::function<void(EventsLooperThread *, int, int, Point, Point)>& push_function) override;

    Point getRelativePoint(int row, int column);

    ~TerrainController() override;
};


#endif //__TERRAIN_CONTROLLER_H__
