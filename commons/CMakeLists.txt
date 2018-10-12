add_library(commons socket_t.c Socket.cpp ClientClosedSocketException.cpp ConnectionRefusedException.cpp)

install(TARGETS commons
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
