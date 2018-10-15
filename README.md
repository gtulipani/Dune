# Dune
## Building and Running
### Build
The Application has 4 different [CMake](https://en.wikipedia.org/wiki/CMake) 
files:
- One CMake at the root path from the project that defines each one of the goals
- One CMake under `server` directory that builds all the server-related files
- One CMake under `client` directory that builds all the client-related files
- One CMake under `commons` directory that builds a [Static Library](https://en.wikipedia.org/wiki/Static_library)
with the shared resources between the server and the client

Following the CMake good practices, create a new directory called 
`cmake-build` in the root from the project and execute: `cmake ..`. This will
create the corresponding [Makefile](https://en.wikipedia.org/wiki/Makefile) for
every CMake following the same directory hierarchy as in the project.
#### Build Commons Library
1. Execute `make commons`. This will create the static library called: 
`libcommons.a`
The output should be similar to:
```
[ 16%] Building C object commons/CMakeFiles/commons.dir/socket_t.c.o
[ 33%] Building CXX object commons/CMakeFiles/commons.dir/Socket.cpp.o
[ 50%] Building CXX object commons/CMakeFiles/commons.dir/ClientClosedSocketException.cpp.o
[ 66%] Building CXX object commons/CMakeFiles/commons.dir/ConnectionRefusedException.cpp.o
[ 83%] Building CXX object commons/CMakeFiles/commons.dir/BadFileException.cpp.o
[100%] Linking CXX static library libcommons.a
[100%] Built target commons
```
#### Build Server
1. Execute `make server`. This will create and executable called: `server`.
The output should be similar to:
```
[ 54%] Built target commons
[ 63%] Building CXX object server/CMakeFiles/server.dir/main.cpp.o
[ 72%] Building CXX object server/CMakeFiles/server.dir/PathFinder.cpp.o
[ 81%] Building CXX object server/CMakeFiles/server.dir/Matrix.cpp.o
[ 90%] Building CXX object server/CMakeFiles/server.dir/Terrain.cpp.o
[100%] Linking CXX executable server
[100%] Built target server
```
#### Build Client
1. Execute `make client`. This will create and executable called: `client`.
The output should be similar to:
```
[ 75%] Built target commons
[ 87%] Building CXX object client/CMakeFiles/client.dir/main.cpp.o
[100%] Linking CXX executable client
[100%] Built target client
```

#### Install Application
1. Execute `make install`. This will install the Application in the machine. 
The output should be similar to:
```
[ 46%] Built target commons
[ 84%] Built target server
[100%] Built target client
Install the project...
-- Install configuration: "Debug"
-- Installing: /usr/local/bin/server
-- Installing: /usr/local/bin/client
-- Installing: /usr/local/lib/libcommons.a
```
