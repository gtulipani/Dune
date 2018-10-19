add_library(commons Socket.cpp SOException.cpp BadFileException.cpp Thread.cpp Lock.cpp)

install(TARGETS commons
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
