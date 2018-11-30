#ifndef __SPRITES_SUPPLIER_H__
#define __SPRITES_SUPPLIER_H__

// STL Libraries
#include <map>

// Client Libraries
#include "../sdl/SdlTexture.h"

typedef enum ClientSprites {
    CONSTRUCTION_CENTER_ICON = 5,
    WIND_TRAPS_ICON = 6,
    REFINERY_ICON = 7,
    ATREIDES_BARRACKS_ICON = 8,
    HARKONNEN_BARRACKS_ICON = 9,
    ORDOS_BARRACKS_ICON = 10,
    LIGHT_FACTORY_ICON = 11,
    HEAVY_FACTORY_ICON = 12,
    SILO_ICON = 13,
    PALACE_ICON = 14,
    LIGHT_INFANTRY_ICON = 15,
    HEAVY_INFANTRY_ICON = 16,
    TRIKE_ICON = 17,
    RAIDER_ICON = 18,
    ATREIDES_TANK_ICON = 19,
    HARKONNEN_TANK_ICON = 20,
    ORDOS_TANK_ICON = 21,
    HARVESTER_ICON = 22,
    PANEL_BACKGROUND = 23,
    PANEL_BUTTONS_BACKGROUND = 24,
    HEALTH_10 = 25,
    HEALTH_20 = 26,
    HEALTH_30 = 27,
    HEALTH_40 = 28,
    HEALTH_50 = 29,
    HEALTH_60 = 30,
    HEALTH_70 = 31,
    HEALTH_80 = 32,
    HEALTH_90 = 33,
    HEALTH_100 = 34,
    SELECTION_SQUARE = 35,
    CONSTRUCTION_PERCENTAGE_0 = 36,
    CONSTRUCTION_PERCENTAGE_12 = 37,
    CONSTRUCTION_PERCENTAGE_25 = 38,
    CONSTRUCTION_PERCENTAGE_37 = 39,
    CONSTRUCTION_PERCENTAGE_50 = 40,
    CONSTRUCTION_PERCENTAGE_62 = 41,
    CONSTRUCTION_PERCENTAGE_75 = 42,
    CONSTRUCTION_PERCENTAGE_87 = 43,
    CONSTRUCTION_PERCENTAGE_100 = 44,
    EAGLE_EYE_SQUARE = 45,
    STATUS_BAR = 46
} ClientSprites;

class ClientSpritesSupplier {
private:
    std::map<int, SdlTexture*> sprites;

    SdlTexture *createTexture(const std::string& subpath, const std::string& file_path, SdlWindow *window);

    SdlTexture *createPanelTexture(const std::string& file_path, SdlWindow *window);
    SdlTexture *createTerrainTexture(const std::string& file_path, SdlWindow *window);
    SdlTexture *createStatusTexture(const std::string& file_path, SdlWindow *window);

public:
    explicit ClientSpritesSupplier(SdlWindow *window);

    // Overloading the assignment by copy
    ClientSpritesSupplier &operator=(const ClientSpritesSupplier &other) = delete;

    // Overloading the assignment by movement
    ClientSpritesSupplier &operator=(ClientSpritesSupplier &&other) noexcept;

    SdlTexture* operator[](enum ClientSprites sprite) const;
    SdlTexture* operator[](int sprite) const;

    ~ClientSpritesSupplier();
};


#endif //__SPRITES_SUPPLIER_H__
