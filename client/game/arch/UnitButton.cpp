#include "UnitButton.h"

// Client Libraries
#include "Area.h"

UnitButton::UnitButton(int width,
                       int height,
                       Point screen_position,
                       int type,
                       SdlTexture* texture,
                       std::vector<int> actions,
                       ClientSpritesSupplier &sprites_supplier) : PanelButton(
       width,
       height,
       std::move(screen_position),
       type,
       texture,
       std::move(actions),
       sprites_supplier) {}

UnitButton::UnitButton(int width,
                       int height,
                       Point screen_position,
                       int type,
                       std::string image_path,
                       std::vector<int> actions,
                       SdlWindow *window,
                       ClientSpritesSupplier &sprites_supplier) : UnitButton(
        width,
        height,
        std::move(screen_position),
        type,
        new SdlTexture(image_path, window),
        std::move(actions),
        sprites_supplier) {}

void UnitButton::click(EventsLooperThread* processer, std::function<void(EventsLooperThread*, int, int, Point, Point)> push_function) {}

bool UnitButton::isWaitingForAction() const {
    return false;
}

void UnitButton::resolve(Point position, EventsLooperThread *processer, std::function<void(EventsLooperThread *, int, int, Point, Point)> push_function) {}
