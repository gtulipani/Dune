# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CMAKE_SOURCE_DIR}/commons) # include files from commons

add_executable(server
        main.cpp
        game/model/PathFinder.cpp
        game/model/Matrix.cpp
        game/model/Point.cpp
        game/model/Terrain.cpp
        game/arch/Accepter.cpp
        game/arch/Client.cpp
        game/arch/Game.cpp
        game/arch/Server.cpp
        game/arch/GameConfiguration.cpp
        game/model/Unit.cpp
        game/model/TileUtils.cpp
        game/model/Weapon.h
        game/model/Soldier.h)

target_link_libraries(server commons)

install(TARGETS server RUNTIME DESTINATION bin)
