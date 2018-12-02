#ifndef __TERRAIN_CONTROLLER_H__
#define __TERRAIN_CONTROLLER_H__

// Commons Libraries
#include <Matrix.h>
#include "../../sdl/SdlWindow.h"
#include "../../sdl/SdlTexture.h"
#include "../SdlPicturable.h"

// Client Libraries
#include "Controller.h"
#include "../PlayerColor.h"

struct SDL_MouseButtonEvent;
class EventsLooperThread;
class ScreenInformation;

class TerrainController : public Controller {
private:
    ClientSpritesSupplier &client_sprites_supplier;
    ScreenInformation &screen_information;
    Matrix matrix;
    int terrain_width_tiles;
    int terrain_height_tiles;
    int terrain_width;
    int terrain_height;
    bool clicked;
    std::map<int, SdlTexture*> terrains_textures_map;
    // Map of string Type / int direction / int motion / enum PlayerColor
    std::map<std::string, std::map<int, std::map<int, std::map<int, SdlTexture*>>>> picturables_map;
    SdlTexture *terrain_texture;

    std::vector<SdlPicturable*> picturables;

    Point temporary_position{};

    void renderEagleEye();

    void buildTerrains();
    void buildUnitsForPlayer(enum PlayerColor player_color);
    void buildEspecia();
    void buildUnits();
    void buildTerrainTexture();
    void preloadTerrainMatrix();

    // Creates a texture by the path and subpath received as parameters
    SdlTexture *createTexture(const std::string& subpath, const std::string& file_path);
    SdlTexture *createPicturableTexture(const std::string& file_path);
    // Creates a texture and assigns a color
    SdlTexture *createPicturableTexture(const std::string& file_path, SdlColor *color);
    SdlTexture *createTerrainTexture(const std::string& file_path);
public:
    TerrainController(int player_id, SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier, ScreenInformation &screen_manager, const ScreenConfiguration& screen_configuration, const Matrix& matrix);

    void update(const GameStatusEvent &event) override;

    void render() override;

    void move(enum Movement movement) override;

    bool resolvePendingAction(const SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer, const std::function<void(EventsLooperThread *, int, int, Point, Point)>& push_function) override;
    void parseMouseClick(const SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, const std::function<void(EventsLooperThread*, int, int, Point, Point)>& push_function) override;
    void parseMouseRelease(const SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer, const std::function<void(EventsLooperThread *, int, int, Point, Point)>& push_function) override;

    ~TerrainController() override;
};


#endif //__TERRAIN_CONTROLLER_H__
