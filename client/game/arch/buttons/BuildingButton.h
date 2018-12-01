#ifndef __BUILDING_BUTTON_H__
#define __BUILDING_BUTTON_H__

// Client Libraries
#include "PanelButton.h"

class BuildingButton : public PanelButton {
public:
    BuildingButton(int width, int height, const std::string& type, int icon_type, std::vector<int> actions, ClientSpritesSupplier &sprites_supplier);

    BuildingButton(int width, int height, const std::string& type, SdlTexture* texture, std::vector<int> actions, ClientSpritesSupplier &sprites_supplier);

    void click(EventsLooperThread* processer, std::function<void(EventsLooperThread*, int, int, Point, Point)> push_function) override;

    void resolve(const Point& position, EventsLooperThread *processer, std::function<void(EventsLooperThread *, int, int, Point, Point)> push_function) override;

    bool isWaitingForAction() const override;

    ~BuildingButton() override = default;
};


#endif //__BUILDING_BUTTON_H__
