#ifndef __PANEL_BUTTON_H__
#define __PANEL_BUTTON_H__

// Commons Libraries
#include <Point.h>

// Client Libraries
#include "../sdl/SdlTexture.h"
#include "ClientSpritesSupplier.h"

#define BUTTON_ORIGINAL_WIDTH 80
#define BUTTON_ORIGINAL_HEIGHT 80

class EventsLooperThread;

class PanelButton {
protected:
    int width;
    int height;
    Point screen_position;
    std::string action;
    SdlTexture *texture;
    ClientSpritesSupplier &sprites_supplier;
    bool have_I_changed;

public:
    PanelButton(int width, int height, Point screen_position, std::string action, SdlTexture *texture, ClientSpritesSupplier &sprites_supplier);

    PanelButton(int width, int height, Point screen_position, std::string action, std::string image_path, SdlWindow* window, ClientSpritesSupplier &sprites_supplier);

    virtual void render(int offset_x, int offset_y) = 0;

    bool includesPosition(Point point) const;

    bool includesExternalAction() const;

    virtual void click(EventsLooperThread* processer, std::function<void(EventsLooperThread*, std::string, Point, Point)> push_function) = 0;

    virtual void disable() = 0;

    std::string getAction() const;

    bool hasChanged() const;

    virtual ~PanelButton();
};


#endif //__PANEL_BUTTON_H__
