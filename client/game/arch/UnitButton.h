#ifndef __UNIT_BUTTON_H__
#define __UNIT_BUTTON_H__

#include "PanelButton.h"

class UnitButton : public PanelButton {
public:
    UnitButton(int width, int height, Point screen_position, int type, SdlTexture *texture, std::vector<int> actions, ClientSpritesSupplier &sprites_supplier);

    UnitButton(int width, int height, Point screen_position, int type, std::string image_path, std::vector<int> actions, SdlWindow* window, ClientSpritesSupplier &sprites_supplier);

    void click(EventsLooperThread* processer, std::function<void(EventsLooperThread*, int, int, Point, Point)> push_function) override;

    bool isWaitingForAction() const override;

    void resolve(Point position, EventsLooperThread *processer, std::function<void(EventsLooperThread *, int, int, Point, Point)> push_function) override;

    ~UnitButton() override = default;
};


#endif //__UNIT_BUTTON_H__
