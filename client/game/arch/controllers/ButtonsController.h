#ifndef __BUTTONS_CONTROLLER_H__
#define __BUTTONS_CONTROLLER_H__

// STL Libraries
#include <vector>

// Commons Libraries
#include <Picturable.h>

// Client Libraries
#include "../../sdl/SdlWindow.h"
#include "../../sdl/SdlTexture.h"
#include "../buttons/PanelButton.h"
#include "../ClientSpritesSupplier.h"
#include "../ScreenConfiguration.h"
#include "Controller.h"

class ScreenInformation;

class ButtonsController : public Controller {
private:
    ClientSpritesSupplier &client_sprites_supplier;
    ScreenInformation &screen_information;
    bool clicked;
    bool panel_rendered;
    SdlTexture *panel_texture;

    std::vector<PanelButton*> available_buttons{};

    void buildTerrainTexture();

    void renderPanel();

    void updateAvailableObjects(const std::vector<std::string>& available_objects);
    void processPicturables(std::vector<Picturable>& picturables);
    void locateButtons();

    Point getGlobalPosition(Point point);

    // This method is used to calculate the position for each one of the panel buttons icons, which are one above each other
    Point buildOptionalButtonRelativePosition(int row_order, int col_order);

    // Render only once the pannel with the main background images and the main buttons
    void buildPanelTexture();
public:
    ButtonsController(unsigned int player_id, SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier, ScreenInformation &screen_manager, const ScreenConfiguration& screen_configuration);

    void update(const GameStatusEvent &event) override;

    void render() override;

    void move(enum Movement movement) override;

    bool resolvePendingAction(const SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer, const std::function<void(EventsLooperThread *, int, int, Point, Point)>& push_function) override;
    void parseMouseClick(const SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, const std::function<void(EventsLooperThread*, int, int, Point, Point)>& push_function) override;
    void parseMouseRelease(const SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, const std::function<void(EventsLooperThread*, int, int, Point, Point)>& push_function) override;

    ~ButtonsController() override;
};


#endif //__BUTTONS_CONTROLLER_H__
