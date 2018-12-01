#ifndef __UNIT_BUTTON_H__
#define __UNIT_BUTTON_H__

#include "PanelButton.h"

class UnitButton : public PanelButton {
public:
    UnitButton(int width, int height, const std::string& type, int icon_type, int action, ClientSpritesSupplier &sprites_supplier);

    UnitButton(int width, int height, const std::string& type, SdlTexture *texture, int action, ClientSpritesSupplier &sprites_supplier);

    void click(EventsLooperThread* processer, std::function<void(EventsLooperThread*, int, int, Point, Point)> push_function) override;

    bool isWaitingForAction() const override;

    void resolve(const Point& position, EventsLooperThread *processer, std::function<void(EventsLooperThread *, int, int, Point, Point)> push_function) override;

    ~UnitButton() override = default;
};


#endif //__UNIT_BUTTON_H__
