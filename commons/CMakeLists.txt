add_library(commons
        BadFileException.cpp
        events/ClientEvent.cpp
        events/EventHandler.cpp
        json/json.hpp
        json/JSONConversion.cpp
        json/JSONUtils.cpp
        Lock.cpp
        Matrix.cpp
        Point.cpp
        Socket.cpp
        SOException.cpp
        Thread.cpp
        TileUtils.cpp
        events/MapConfigurationEvent.cpp
        events/GameStatusEvent.cpp
        Picturable.cpp
        events/NotificationEvent.cpp)

install(TARGETS commons
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
