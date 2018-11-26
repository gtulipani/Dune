#ifndef __MAIN_BUTTON_H__
#define __MAIN_BUTTON_H__

#include "PanelButton.h"

class MainButton : public PanelButton {
public:
    MainButton(int width, int height, Point screen_position, std::string action, SdlTexture *texture, ClientSpritesSupplier &sprites_supplier);

    MainButton(int width, int height, Point screen_position, std::string action, std::string image_path, SdlWindow* window, ClientSpritesSupplier &sprites_supplier);

    void render(int offset_x, int offset_y) override;

    void click(EventsLooperThread* processer, std::function<void(EventsLooperThread*, std::string, Point, Point)> push_function) override;

    void disable() override;

    ~MainButton() override = default;
};


#endif //__MAIN_BUTTON_H__
