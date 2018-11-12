add_library(commons
        events/ClientEvent.cpp
        events/EventHandler.cpp
        events/GameStatusEvent.cpp
        events/MapConfigurationEvent.cpp
        events/NotificationEvent.cpp
        json/json.hpp
        json/JSONConversion.cpp
        json/JSONUtils.cpp
        BadFileException.cpp
        Lock.cpp
        Matrix.cpp
        Picturable.cpp
        PicturableType.h
        Point.cpp
        shaque.h
        Socket.cpp
        SOException.cpp
        TerrainType.h
        Thread.cpp
        TileUtils.cpp)

install(TARGETS commons
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
