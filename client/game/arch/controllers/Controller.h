#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

// STL Libraries
#include <functional>

// Client Libraries
#include "../ScreenConfiguration.h"
#include "../ScreenInformation.h"

struct SDL_MouseButtonEvent;
class Point;
class EventsLooperThread;
class SdlWindow;
class GameStatusEvent;

class Controller {
protected:
    SdlWindow *window;
    ScreenConfiguration screen_configuration;
    bool pending_changes;

    bool notIncludes(int x, int y);
    bool includes(int x, int y);

public:
    Controller(SdlWindow *window, const ScreenConfiguration& screen_configuration, bool pending_changes);

    Controller(const Controller &other) = delete;

    // Overloading the assignment by copy
    Controller &operator=(const Controller &other) = delete;

    void fill();

    void refresh();

    virtual void update(const GameStatusEvent &event) = 0;

    virtual void render() = 0;

    virtual void move(enum Movement movement) = 0;

    virtual bool resolvePendingAction(const SDL_MouseButtonEvent &mouse_event, EventsLooperThread *processer, const std::function<void(EventsLooperThread *, int, int, Point, Point)>& push_function) = 0;

    virtual void parseMouseClick(const SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, const std::function<void(EventsLooperThread*, int, int, Point, Point)>& push_function) = 0;
    virtual void parseMouseRelease(const SDL_MouseButtonEvent& mouse_event, EventsLooperThread* processer, const std::function<void(EventsLooperThread*, int, int, Point, Point)>& push_function) = 0;

    virtual ~Controller() = 0;
};


#endif //__CONTROLLER_H__
