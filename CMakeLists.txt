cmake_minimum_required(VERSION 3.12)
project(Dune)

# Set C++ Compiler Flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -pthread -ggdb -DJSON_MultipleHeaders=ON")

add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(commons)
add_subdirectory(editor)
