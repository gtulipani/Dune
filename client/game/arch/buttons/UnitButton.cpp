#include <events/ClientEvent.h>
#include "UnitButton.h"

// Client Libraries
#include "../Area.h"

UnitButton::UnitButton(int width,
                       int height,
                       const std::string& type,
                       int icon_type,
                       int action,
                       ClientSpritesSupplier &sprites_supplier) : PanelButton(
        width,
        height,
        type,
        sprites_supplier[icon_type],
        {action},
        sprites_supplier) {}


UnitButton::UnitButton(int width,
                       int height,
                       const std::string& type,
                       SdlTexture* texture,
                       int action,
                       ClientSpritesSupplier &sprites_supplier) : PanelButton(
       width,
       height,
       type,
       texture,
       {action},
       sprites_supplier) {}

void UnitButton::click(EventsLooperThread* processer, std::function<void(EventsLooperThread*, int, int, Point, Point)> push_function) {
    if (!is_being_created) {
        // If it's not during creation, then it can be clicked
        push_function(processer, actions[0], 0, screen_position, screen_position);
        disable();
    }
}

bool UnitButton::isWaitingForAction() const {
    return false;
}

void UnitButton::resolve(const Point& position, EventsLooperThread *processer, std::function<void(EventsLooperThread *, int, int, Point, Point)> push_function) {}
