#include "ButtonsFactory.h"

// Commons Libraries
#include <UnitsAndBuildings.h>
#include <events/ClientEvent.h>

// Client Libraries
#include "BuildingButton.h"
#include "../controllers/ScreenController.h"

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
        return createBuildingButton(BARRACKS, ATREIDES_BARRACKS_ICON, CREATE_ATREIDES_BARRACKS_TYPEv, client_sprites_supplier);
    } else if (name == LIGHT_FACTORY) {
        return createBuildingButton(LIGHT_FACTORY, LIGHT_FACTORY_ICON, CREATE_LIGHT_FACTORY_TYPE, client_sprites_supplier);
    } else if (name == HEAVY_FACTORY) {
        return createBuildingButton(HEAVY_FACTORY, HEAVY_FACTORY_ICON, CREATE_HEAVY_FACTORY_TYPE, client_sprites_supplier);
    } else if (name == SILO) {
        return createBuildingButton(SILO, SILO_ICON, CREATE_SILO_TYPE, client_sprites_supplier);
    };
}
