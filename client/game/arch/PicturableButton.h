#ifndef __PICTURABLE_BUTTON_H__
#define __PICTURABLE_BUTTON_H__


#include "PanelButton.h"

class PicturableButton : public PanelButton {
private:
    bool requires_second_action;

    bool is_being_created;
    int progress;

    int picturable_id{};

    SdlTexture* getProgressTexture();
public:
    PicturableButton(int width, int height, Point screen_position, std::vector<int> actions, SdlTexture *texture, ClientSpritesSupplier &sprites_supplier, bool requires_second_action);

    PicturableButton(int width, int height, Point screen_position, std::vector<int> actions, std::string image_path, SdlWindow* window, ClientSpritesSupplier &sprites_supplier, bool requires_second_action);

    void render(int offset_x, int offset_y) override;

    void click(EventsLooperThread* processer, std::function<void(EventsLooperThread*, int, std::vector<int>, Point, Point)> push_function) override;

    void disable() override;

    void resolve(Point position, EventsLooperThread *processer, std::function<void(EventsLooperThread *, int, std::vector<int>, Point, Point)> push_function) override;

    bool hasPendingAction() override;

    ~PicturableButton() override = default;
};


#endif //__PICTURABLE_BUTTON_H__
