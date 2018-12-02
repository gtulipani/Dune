#include "ButtonsFactory.h"

// Commons Libraries
#include <UnitsAndBuildings.h>
#include <events/ClientEvent.h>

// Client Libraries
#include "BuildingButton.h"
#include "UnitButton.h"
#include "../ScreenInformation.h"

PanelButton* ButtonsFactory::createUnitButton(const std::string& name, int icon, int action, ClientSpritesSupplier &client_sprites_supplier) {
    return new UnitButton(PANEL_BUTTON_ICON_WIDTH, PANEL_BUTTON_ICON_HEIGHT, name, icon, action, client_sprites_supplier);
}

PanelButton* ButtonsFactory::createBuildingButton(const std::string& name, int icon, int action, ClientSpritesSupplier &client_sprites_supplier) {
    return new BuildingButton(PANEL_BUTTON_ICON_WIDTH, PANEL_BUTTON_ICON_HEIGHT, name, icon,
            {action, LOCATE_BUILDING_TYPE},
            client_sprites_supplier);
}

PanelButton* ButtonsFactory::createButton(const std::string& name, ClientSpritesSupplier &client_sprites_supplier) {
    if (name == CONSTRUCTION_CENTER) {
        return createBuildingButton(CONSTRUCTION_CENTER, CONSTRUCTION_CENTER_ICON, CREATE_CONSTRUCTION_CENTER, client_sprites_supplier);
    } else if (name == WIND_TRAPS) {
        return createBuildingButton(WIND_TRAPS, WIND_TRAPS_ICON, CREATE_WIND_TRAPS_TYPE, client_sprites_supplier);
    } else if (name == REFINERY) {
        return createBuildingButton(REFINERY, REFINERY_ICON, CREATE_REFINERY_TYPE, client_sprites_supplier);
    } else if (name == BARRACKS) {
        return createBuildingButton(BARRACKS, BARRACKS_ICON, CREATE_BARRACKS_TYPE, client_sprites_supplier);
    } else if (name == LIGHT_FACTORY) {
        return createBuildingButton(LIGHT_FACTORY, LIGHT_FACTORY_ICON, CREATE_LIGHT_FACTORY_TYPE, client_sprites_supplier);
    } else if (name == HEAVY_FACTORY) {
        return createBuildingButton(HEAVY_FACTORY, HEAVY_FACTORY_ICON, CREATE_HEAVY_FACTORY_TYPE, client_sprites_supplier);
    } else if (name == SILO) {
        return createBuildingButton(SILO, SILO_ICON, CREATE_SILO_TYPE, client_sprites_supplier);
    } else if (name == TRIKE) {
        return createUnitButton(TRIKE, TRIKE_ICON, CREATE_TRIKE_TYPE, client_sprites_supplier);
    } else if (name == RAIDER) {
        return createUnitButton(RAIDER, RAIDER_ICON, CREATE_RAIDER_TYPE, client_sprites_supplier);
    } else if (name == TANK) {
        return createUnitButton(TANK, TANK_ICON, CREATE_TANK_TYPE, client_sprites_supplier);
    } else if (name == HARVESTER) {
        return createUnitButton(HARVESTER, HARVESTER_ICON, CREATE_HARVESTER_TYPE, client_sprites_supplier);
    } else if (name == LIGHT_INFANTRY) {
        return createUnitButton(LIGHT_INFANTRY, LIGHT_INFANTRY_ICON, CREATE_LIGHT_INFANTRY_TYPE, client_sprites_supplier);
    } else {
        return createUnitButton(HEAVY_INFANTRY, HEAVY_INFANTRY_ICON, CREATE_HEAVY_INFANTRY_TYPE, client_sprites_supplier);
    };
}
