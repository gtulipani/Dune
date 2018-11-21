#include "ClientSpritesSupplier.h"

#define CLIENT_RESOURCES_PATH std::string("resources/images/game/client/")
#define PANEL_RESOURCES_SUBPATH std::string("panel/")
#define TERRAIN_RESOURCES_SUBPATH std::string("terrain/")

SdlTexture *ClientSpritesSupplier::createTexture(const std::string& subpath, const std::string& file_path, SdlWindow *window) {
    return new SdlTexture(CLIENT_RESOURCES_PATH + subpath + file_path, window);
}

SdlTexture *ClientSpritesSupplier::createPanelTexture(const std::string& file_path, SdlWindow *window) {
    return createTexture(PANEL_RESOURCES_SUBPATH, file_path, window);
}

SdlTexture *ClientSpritesSupplier::createTerrainTexture(const std::string& file_path, SdlWindow *window) {
    return createTexture(TERRAIN_RESOURCES_SUBPATH, file_path, window);
}

ClientSpritesSupplier::ClientSpritesSupplier(SdlWindow *window) {
    // Store main buttons icons textures
    sprites.emplace(REPAIR_BUTTON_ICON, createPanelTexture("repair_button.png", window));
    sprites.emplace(SELL_BUTTON_ICON, createPanelTexture("sell_button.png", window));
    sprites.emplace(STATUS_BUTTON_ICON, createPanelTexture("status_button.png", window));
    sprites.emplace(GUARD_BUTTON_ICON, createPanelTexture("guard_button.png", window));
    sprites.emplace(RETREAT_BUTTON_ICON, createPanelTexture("retreat_button.png", window));

    // Store buildings icons textures
    //sprites.emplace(CONSTRUCTION_CENTER_ICON, createButtonTexture("construction_center_icon.png"));
    sprites.emplace(WIND_TRAPS_ICON, createPanelTexture("wind_trap_icon.png", window));
    sprites.emplace(REFINERY_ICON, createPanelTexture("refinery_icon.png", window));
    sprites.emplace(ATREIDES_BARRACKS_ICON, createPanelTexture("atreides_barracks_icon.png", window));
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
    sprites.emplace(ATREIDES_TANK_ICON, createPanelTexture("atreides_tank_icon.png", window));
    sprites.emplace(HARKONNEN_TANK_ICON, createPanelTexture("harkonnen_tank_icon.png", window));
    sprites.emplace(ORDOS_TANK_ICON, createPanelTexture("ordos_tank_icon.png", window));
    sprites.emplace(HARVESTER_ICON, createPanelTexture("harvester_icon.png", window));

    // Store background images textures
    sprites.emplace(BACKGROUND, createPanelTexture("background.png", window));
    sprites.emplace(BUTTONS_BACKGROUND, createPanelTexture("optional_buttons_background.png", window));

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
