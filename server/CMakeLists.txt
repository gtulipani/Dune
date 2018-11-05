# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CMAKE_SOURCE_DIR}/commons) # include files from commons

add_executable(server
        main.cpp
        game/arch/Accepter.cpp
        game/arch/Client.cpp
        game/arch/Game.cpp
        game/arch/GameConfiguration.cpp
        game/arch/Server.cpp
        game/model/GameObject.cpp
        game/model/WalkingUnit.cpp)

target_link_libraries(server commons)

install(TARGETS server RUNTIME DESTINATION bin)
