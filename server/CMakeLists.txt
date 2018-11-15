# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CMAKE_SOURCE_DIR}/commons) # include files from commons

add_executable(server
        main.cpp
        game/json/JSONConversion.cpp
        game/arch/Accepter.cpp
        game/arch/ClientThread.cpp
        game/arch/GameConfiguration.cpp
        game/arch/ConfigMap.cpp
        game/arch/Game.cpp
        game/arch/ServerThread.cpp
        game/arch/EventsHandler.cpp
        game/model/GameObject.cpp
        game/model/WalkingUnit.cpp
        game/model/Map.cpp)

target_link_libraries(server commons)

install(TARGETS server RUNTIME DESTINATION bin)
