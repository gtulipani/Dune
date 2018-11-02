add_library(commons
        BadFileException.cpp
        Event.cpp
        json.hpp
        JSONUtils.cpp
        Lock.cpp
        Map.cpp
        Matrix.cpp
        PathFinder.cpp
        Point.cpp
        Socket.cpp
        SOException.cpp
        Terrain.cpp
        Thread.cpp
        TileUtils.cpp
        Unit.cpp Event.cpp Event.h)

install(TARGETS commons
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
