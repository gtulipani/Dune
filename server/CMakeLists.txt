# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS editor/ui)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/commons) # include files from commons
include_directories(editor/include) # include files from the editor

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
        game/model/Soldier.h
        editor/src/Editor.cpp
        editor/src/TerrainCellWidget.cpp )

target_link_libraries(server commons Qt5::Widgets)

install(TARGETS server RUNTIME DESTINATION bin)
