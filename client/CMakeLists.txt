add_executable(client main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/commons) # include files from commons
target_link_libraries(client commons)

install(TARGETS client RUNTIME DESTINATION bin)
