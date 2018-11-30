#ifndef __PANEL_BUTTON_H__
#define __PANEL_BUTTON_H__

// Commons Libraries
#include <Point.h>

// Client Libraries
#include "../../sdl/SdlTexture.h"
#include "../ClientSpritesSupplier.h"

#define BUTTON_ORIGINAL_WIDTH 80
#define BUTTON_ORIGINAL_HEIGHT 80

class EventsLooperThread;

class PanelButton {
protected:
    int width;
    int height;
    std::string name;
    SdlTexture *texture;
    std::vector<int> actions;
    ClientSpritesSupplier &sprites_supplier;
    bool valid;
    bool have_I_changed;
    bool is_being_created;
    bool finished_creating;
    int progress;

    Point screen_position{};
    int picturable_id{};

    SdlTexture* getProgressTexture();
public:
    PanelButton(int width, int height, std::string name, SdlTexture *texture, std::vector<int> actions, ClientSpritesSupplier &sprites_supplier);

    PanelButton(int width, int height, std::string name, std::string image_path, std::vector<int> actions, SdlWindow* window, ClientSpritesSupplier &sprites_supplier);

    void locate(const Point& point);

    void render(int offset_x, int offset_y);

    bool includesPosition(Point point) const;

    bool includesExternalAction() const;

    bool hasChanged() const;

    std::string getName() const;

    bool isValid() const;

    void setValid();

    void setInvalid();

    void disable();

    bool update(int picturable_id, int progress);

    virtual void click(EventsLooperThread* processer, std::function<void(EventsLooperThread*, int, int, Point, Point)> push_function) = 0;

    virtual void resolve(Point position, EventsLooperThread *processer, std::function<void(EventsLooperThread *, int, int, Point, Point)> push_function) = 0;

    virtual bool isWaitingForAction() const = 0;

    virtual ~PanelButton();
};


#endif //__PANEL_BUTTON_H__
