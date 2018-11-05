add_library(commons
        BadFileException.cpp
        Event.cpp
        EventHandler.cpp
        json.hpp
        JSONConversion.cpp
        JSONUtils.cpp
        Lock.cpp
        Matrix.cpp
        PathFinder.cpp
        Point.cpp
        Socket.cpp
        SOException.cpp
        Terrain.cpp
        Thread.cpp
        TileUtils.cpp
        Unit.cpp)

install(TARGETS commons
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
