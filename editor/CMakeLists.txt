# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/commons) # include files from commons
include_directories(include) # include files from the editor

add_executable(editor
        main.cpp
        src/Editor.cpp
        src/TerrainCellWidget.cpp)

target_link_libraries(editor commons Qt5::Widgets)

install(TARGETS editor RUNTIME DESTINATION bin)
