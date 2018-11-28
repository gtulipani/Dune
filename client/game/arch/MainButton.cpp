#include "MainButton.h"

// Client Libraries
#include "Area.h"

MainButton::MainButton(int width,
                       int height,
                       Point screen_position,
                       std::vector<int> actions,
                       SdlTexture* texture,
                       ClientSpritesSupplier &sprites_supplier) : PanelButton(
       width,
       height,
       std::move(screen_position),
       std::move(actions),
       texture,
       sprites_supplier) {}

MainButton::MainButton(int width,
                       int height,
                       Point screen_position,
                       std::vector<int> actions,
                       std::string image_path,
                       SdlWindow *window,
                       ClientSpritesSupplier &sprites_supplier) : MainButton(
        width,
        height,
        std::move(screen_position),
        std::move(actions),
        new SdlTexture(image_path, window),
        sprites_supplier) {}

void MainButton::render(int offset_x, int offset_y) {
    Area srcArea(0, 0, BUTTON_ORIGINAL_WIDTH, BUTTON_ORIGINAL_HEIGHT);
    Area destArea(offset_x + this->screen_position.col, offset_y + this->screen_position.row, this->width,
                  this->height);
    this->texture->render(srcArea, destArea);
}

void MainButton::click(EventsLooperThread* processer, std::function<void(EventsLooperThread*, int, std::vector<int>, Point, Point)> push_function) {}

void MainButton::disable() {}

void MainButton::resolve(Point position, EventsLooperThread *processer, std::function<void(EventsLooperThread *, int, std::vector<int>, Point, Point)> push_function) {}

bool MainButton::hasPendingAction() {
    return false;
}
