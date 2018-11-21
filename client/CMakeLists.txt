set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Dune_SOURCE_DIR}/client/cmake-sdl")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(client
    main.cpp
        game/arch/Area.cpp
        game/arch/BlockingQueue.hpp
        game/arch/ButtonsController.cpp
        game/arch/Client.cpp
        game/arch/EventsLooperThread.cpp
        game/arch/EventsReceptorThread.cpp
        game/arch/EventsSenderThread.cpp
        game/arch/PanelButton.cpp
        game/arch/SdlPicturable.cpp
        game/arch/ClientSpritesSupplier.cpp
        game/arch/TerrainController.cpp
        game/arch/WindowController.cpp
        game/sdl/SdlException.cpp
        game/sdl/SdlTexture.cpp
        game/sdl/SdlWindow.cpp)

# Include files from SDL2
include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR})
# Include files from commons
include_directories(${CMAKE_SOURCE_DIR}/commons)

target_link_libraries(client commons ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

install(TARGETS client RUNTIME DESTINATION bin)
