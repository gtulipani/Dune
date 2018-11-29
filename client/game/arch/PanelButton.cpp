#include "PanelButton.h"
#include "Area.h"

PanelButton::PanelButton(int width,
                         int height,
                         Point screen_position,
                         int type,
                         SdlTexture* texture,
                         std::vector<int> actions,
                         ClientSpritesSupplier &sprites_supplier) :
        width(width),
        height(height),
        screen_position(std::move(screen_position)),
        type(type),
        texture(texture),
        actions(std::move(actions)),
        sprites_supplier(sprites_supplier),
        have_I_changed(false),
        is_being_created(false),
        finished_creating(false),
        progress(100) {}

PanelButton::PanelButton(int width,
                         int height,
                         Point screen_position,
                         int type,
                         std::string image_path,
                         std::vector<int> actions,
                         SdlWindow *window,
                         ClientSpritesSupplier &sprites_supplier) : PanelButton(
        width,
        height,
        std::move(screen_position),
        type,
        new SdlTexture(image_path, window),
        std::move(actions),
        sprites_supplier) {}

SdlTexture* PanelButton::getProgressTexture() {
    if (this->progress == 100) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_100];
    }
    if (this->progress >= 87) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_87];
    }
    if (this->progress >= 75) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_75];
    }
    if (this->progress >= 62) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_62];
    }
    if (this->progress >= 50) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_50];
    }
    if (this->progress >= 37) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_37];
    }
    if (this->progress >= 25) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_25];
    }
    if (this->progress >= 12) {
        return sprites_supplier[CONSTRUCTION_PERCENTAGE_12];
    }
    return sprites_supplier[CONSTRUCTION_PERCENTAGE_0];
}

void PanelButton::render(int offset_x, int offset_y) {
    Area srcArea(0, 0, BUTTON_ORIGINAL_WIDTH, BUTTON_ORIGINAL_HEIGHT);
    Area destArea(offset_x + screen_position.col, offset_y + screen_position.row, width, height);
    texture->render(srcArea, destArea);
    // If is being created (progress is changing) or it finished creating and waiting for user action
    if (is_being_created || finished_creating) {
        getProgressTexture()->render(srcArea, destArea);
    }
    have_I_changed = false;
}

bool PanelButton::includesPosition(Point point) const {
    // Returns true if the point received as parameter is contained inside the limit determined by the
    // screen_position, the width and the height
    return
            ((this->screen_position.col <= point.col) &&
             (point.col <= (this->screen_position.col + this->width)) &&
             (this->screen_position.row <= point.row) &&
             (point.row <= (this->screen_position.row + this->height)));
}

bool PanelButton::includesExternalAction() const {
    return !actions.empty();
}

bool PanelButton::hasChanged() const {
    return have_I_changed;
}

bool PanelButton::hasType(int type) const {
    return (this->type == type);
}

bool PanelButton::update(int picturable_id, int progress) {
    bool updated = false;
    this->picturable_id = picturable_id;
    // Means that I had already finished creating it and I received it anyways. So it means it was located
    if ((progress == 100) && (finished_creating)) {
        this->finished_creating = false;
        updated = true;
    }

    // Means that the progress has changed from the last time
    if (this->progress != progress) {
        // Means that I finished creating the picturable and I'm waiting for another action
        if (progress == 100) {
            this->finished_creating = true;
            this->is_being_created = false;
        }
        this->progress = progress;
        this->have_I_changed = true;
        updated = true;
    }
    return updated;
}

void PanelButton::disable() {
    is_being_created = true;
    progress = 0;
    have_I_changed = true;
}

PanelButton::~PanelButton() = default;
