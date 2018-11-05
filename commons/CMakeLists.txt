add_library(commons
        BadFileException.cpp
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
        TileUtils.cpp)

install(TARGETS commons
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
