#include "ClientSpritesSupplier.h"

#define CLIENT_RESOURCES_PATH std::string("resources/images/game/client/")
#define PANEL_RESOURCES_SUBPATH std::string("panel/")
#define TERRAIN_RESOURCES_SUBPATH std::string("terrain/")
#define STATUS_RESOURCES_SUBPATH std::string("status/")

SdlTexture *ClientSpritesSupplier::createTexture(const std::string& subpath, const std::string& file_path, SdlWindow *window) {
    return new SdlTexture(CLIENT_RESOURCES_PATH + subpath + file_path, window);
}

SdlTexture *ClientSpritesSupplier::createPanelTexture(const std::string& file_path, SdlWindow *window) {
    return createTexture(PANEL_RESOURCES_SUBPATH, file_path, window);
}

SdlTexture *ClientSpritesSupplier::createTerrainTexture(const std::string& file_path, SdlWindow *window) {
    return createTexture(TERRAIN_RESOURCES_SUBPATH, file_path, window);
}

SdlTexture *ClientSpritesSupplier::createStatusTexture(const std::string& file_path, SdlWindow *window) {
    return createTexture(STATUS_RESOURCES_SUBPATH, file_path, window);
}

ClientSpritesSupplier::ClientSpritesSupplier(SdlWindow *window) {
    // Store buildings icons textures
    sprites.emplace(CONSTRUCTION_CENTER_ICON, createPanelTexture("refinery_icon.png", window)); // need to be updated
    sprites.emplace(WIND_TRAPS_ICON, createPanelTexture("wind_trap_icon.png", window));
    sprites.emplace(REFINERY_ICON, createPanelTexture("refinery_icon.png", window));
    sprites.emplace(BARRACKS_ICON, createPanelTexture("atreides_barracks_icon.png", window));
    sprites.emplace(HARKONNEN_BARRACKS_ICON, createPanelTexture("harkonnen_barracks_icon.png", window));
    sprites.emplace(ORDOS_BARRACKS_ICON, createPanelTexture("ordos_barracks_icon.png", window));
    sprites.emplace(LIGHT_FACTORY_ICON, createPanelTexture("light_factory_icon.png", window));
    sprites.emplace(HEAVY_FACTORY_ICON, createPanelTexture("heavy_factory_icon.png", window));
    sprites.emplace(SILO_ICON, createPanelTexture("silo_icon.png", window));
    sprites.emplace(PALACE_ICON, createPanelTexture("palace_icon.png", window));

    // Store units icons textures
    sprites.emplace(LIGHT_INFANTRY_ICON, createPanelTexture("light_infantry_icon.png", window));
    sprites.emplace(HEAVY_INFANTRY_ICON, createPanelTexture("heavy_infantry_icon.png", window));
    sprites.emplace(TRIKE_ICON, createPanelTexture("trike_icon.png", window));
    sprites.emplace(RAIDER_ICON, createPanelTexture("raider_icon.png", window));
    sprites.emplace(TANK_ICON, createPanelTexture("atreides_tank_icon.png", window));
    sprites.emplace(HARKONNEN_TANK_ICON, createPanelTexture("harkonnen_tank_icon.png", window));
    sprites.emplace(ORDOS_TANK_ICON, createPanelTexture("ordos_tank_icon.png", window));
    sprites.emplace(HARVESTER_ICON, createPanelTexture("harvester_icon.png", window));

    // Store panel images textures
    sprites.emplace(PANEL_BACKGROUND, createPanelTexture("background.png", window));
    sprites.emplace(PANEL_BUTTONS_BACKGROUND, createPanelTexture("optional_buttons_background.png", window));
    sprites.emplace(CONSTRUCTION_PERCENTAGE_0, createPanelTexture("progress_0.png", window));
    sprites.emplace(CONSTRUCTION_PERCENTAGE_12, createPanelTexture("progress_12.png", window));
    sprites.emplace(CONSTRUCTION_PERCENTAGE_25, createPanelTexture("progress_25.png", window));
    sprites.emplace(CONSTRUCTION_PERCENTAGE_37, createPanelTexture("progress_37.png", window));
    sprites.emplace(CONSTRUCTION_PERCENTAGE_50, createPanelTexture("progress_50.png", window));
    sprites.emplace(CONSTRUCTION_PERCENTAGE_62, createPanelTexture("progress_62.png", window));
    sprites.emplace(CONSTRUCTION_PERCENTAGE_75, createPanelTexture("progress_75.png", window));
    sprites.emplace(CONSTRUCTION_PERCENTAGE_87, createPanelTexture("progress_87.png", window));
    sprites.emplace(CONSTRUCTION_PERCENTAGE_100, createPanelTexture("progress_100.png", window));
    sprites.emplace(EAGLE_EYE_SQUARE, createPanelTexture("eagle_eye_square.png", window));

    // Store various textures
    sprites.emplace(HEALTH_10, createTerrainTexture("health_10.png", window));
    sprites.emplace(HEALTH_20, createTerrainTexture("health_20.png", window));
    sprites.emplace(HEALTH_30, createTerrainTexture("health_30.png", window));
    sprites.emplace(HEALTH_40, createTerrainTexture("health_40.png", window));
    sprites.emplace(HEALTH_50, createTerrainTexture("health_50.png", window));
    sprites.emplace(HEALTH_60, createTerrainTexture("health_60.png", window));
    sprites.emplace(HEALTH_70, createTerrainTexture("health_70.png", window));
    sprites.emplace(HEALTH_80, createTerrainTexture("health_80.png", window));
    sprites.emplace(HEALTH_90, createTerrainTexture("health_90.png", window));
    sprites.emplace(HEALTH_100, createTerrainTexture("health_100.png", window));
    sprites.emplace(SELECTION_SQUARE, createTerrainTexture("selection_square.png", window));

    // Store status bar texture
    sprites.emplace(STATUS_BAR, createStatusTexture("status_bar.jpg", window));
}

ClientSpritesSupplier &ClientSpritesSupplier::operator=(ClientSpritesSupplier &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->sprites = std::move(other.sprites);

    return *this;
}

SdlTexture* ClientSpritesSupplier::operator[](enum ClientSprites sprite) const {
    return sprites.at(sprite);
}

SdlTexture* ClientSpritesSupplier::operator[](int sprite) const {
    return sprites.at(sprite);
}

ClientSpritesSupplier::~ClientSpritesSupplier() {
    for (auto& sprite: this->sprites) {
        delete sprite.second;
    }
}
