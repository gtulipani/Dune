set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Dune_SOURCE_DIR}/client/cmake-sdl")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(client
        main.cpp
        game/arch/Area.cpp
        game/arch/BlockingQueue.hpp
        game/arch/Client.cpp
        game/arch/ClientPicturable.cpp
        game/arch/ClientSpritesSupplier.cpp
        game/arch/PlayerColor.cpp
        game/arch/ScreenInformation.cpp
        game/arch/ScreenConfiguration.cpp
        game/arch/buttons/BuildingButton.cpp
        game/arch/buttons/PanelButton.cpp
        game/arch/buttons/UnitButton.cpp
        game/arch/buttons/ButtonsFactory.cpp
        game/arch/controllers/ButtonsController.cpp
        game/arch/controllers/Controller.cpp
        game/arch/controllers/RequiresExternalControllerActionException.cpp
        game/arch/controllers/StatusController.cpp
        game/arch/controllers/TerrainController.cpp
        game/arch/controllers/WindowController.cpp
        game/arch/threads/EventsLooperThread.cpp
        game/arch/threads/EventsReceptorThread.cpp
        game/arch/threads/EventsSenderThread.cpp
        game/sdl/SdlColor.cpp
        game/sdl/SdlException.cpp
        game/sdl/SdlText.cpp
        game/sdl/SdlTexture.cpp
        game/sdl/SdlWindow.cpp)

# Include files from SDL2
include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR})
# Include files from commons
include_directories(${CMAKE_SOURCE_DIR}/commons)

target_link_libraries(client commons ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} SDL2_ttf)

install(TARGETS client RUNTIME DESTINATION bin)
