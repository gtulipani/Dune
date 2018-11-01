add_library(commons
        Socket.cpp
        SOException.cpp
        BadFileException.cpp
        Thread.cpp
        Lock.cpp
        JSONUtils.cpp
        json.hpp)

install(TARGETS commons
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
