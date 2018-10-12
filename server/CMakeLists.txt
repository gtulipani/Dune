add_executable(server main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/commons) # include files from commons
target_link_libraries(server commons)

install(TARGETS server RUNTIME DESTINATION bin)