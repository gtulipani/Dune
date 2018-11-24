#ifndef __PICTURABLE_BUTTON_H__
#define __PICTURABLE_BUTTON_H__


#include "PanelButton.h"

class PicturableButton : public PanelButton {
public:
    PicturableButton(int width, int height, Point screen_position, std::string action, SdlTexture *texture, ClientSpritesSupplier &sprites_supplier);

    PicturableButton(int width, int height, Point screen_position, std::string action, std::string image_path, SdlWindow* window, ClientSpritesSupplier &sprites_supplier);

    void render(int offset_x, int offset_y) override;

    ~PicturableButton() override = default;
};


#endif //__PICTURABLE_BUTTON_H__
