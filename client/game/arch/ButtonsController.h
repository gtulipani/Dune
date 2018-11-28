#ifndef __BUTTONS_CONTROLLER_H__
#define __BUTTONS_CONTROLLER_H__

// STL Libraries
#include <vector>

// Client Libraries
#include "../sdl/SdlWindow.h"
#include "../sdl/SdlTexture.h"
#include "PanelButton.h"
#include "ClientSpritesSupplier.h"

class SDL_MouseButtonEvent;
class EventsLooperThread;
class TerrainController;

class ButtonsController {
private:
    SdlWindow *window;
    ClientSpritesSupplier &client_sprites_supplier;
    TerrainController* terrain_controller;
    std::function<void(TerrainController*, Area)> map_renderer;

    SdlTexture *panel_texture{};

    std::vector<PanelButton*> mandatory_buttons{};
    std::vector<PanelButton*> available_buttons{};

    int screen_width{};
    int screen_height{};

    int screen_width_offset{};

    bool pending_changes{};

    Point getGlobalPosition(Point point);
    Point getRelativePosition(Point point);

    // This method is used to calculate the position for each one of the main buttons, which are one next to each other
    Point buildMainButtonRelativePosition(int order);

    // This method is used to calculate the position for each one of the building icons, which are one above each other
    Point buildOptionalButtonRelativePosition(int order);

    // Load the initial main buttons
    void loadMainButtons();
    // Load the initial buttons from the pannel
    void loadButtonsPanel();
    // Render only once the pannel with the main background images and the main buttons
    void renderPanelTexture();
    // Render the eagle eye map in the panel
    void renderEagleEye();
public:
    // map_renderer is a function that knows how to render the map on a given area
    ButtonsController(SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier, TerrainController* terrain_controller, std::function<void(TerrainController*, Area)> map_renderer);

    void fill();

    void configure(int screen_width, int screen_height, int screen_width_offset);

    void render();

    void refresh();

    bool resolvePendingAction(SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer,
                        std::function<void(EventsLooperThread *, int, std::vector<int>, Point,
                                           Point)> push_function);

    void parseMouseClickButton(SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, std::function<void(EventsLooperThread*, int, std::vector<int>, Point, Point)> push_function);
    void parseMouseReleaseButton(SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, std::function<void(EventsLooperThread*, int, std::vector<int>, Point, Point)> push_function);

    void move();

    ~ButtonsController();
};


#endif //__BUTTONS_CONTROLLER_H__
