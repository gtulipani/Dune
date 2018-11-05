# Dune
## Building and Running
### Build
The Application has 5 different [CMake](https://en.wikipedia.org/wiki/CMake) 
files:
- One CMake at the root path from the project that defines each one of the goals
- One CMake under `server` directory that builds all the server-related files
- One CMake under `client` directory that builds all the client-related files
- One CMake under `editor` directory that builds all the editor-related files
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

#### Build Editor
1. Execute `make editor`. This will create and executable called: `editor`.
The output should be similar to:
```
[ 50%] Built target commons
Scanning dependencies of target editor_autogen
[ 58%] Automatic MOC and UIC for target editor
[ 58%] Built target editor_autogen
Scanning dependencies of target editor
[ 66%] Building CXX object editor/CMakeFiles/editor.dir/main.cpp.o
[ 75%] Building CXX object editor/CMakeFiles/editor.dir/src/Editor.cpp.o
[ 83%] Building CXX object editor/CMakeFiles/editor.dir/src/TerrainCellWidget.cpp.o
[ 91%] Building CXX object editor/CMakeFiles/editor.dir/editor_autogen/mocs_compilation.cpp.o
[100%] Linking CXX executable editor
[100%] Built target editor
```

#### Install Application
1. Execute `make install`. This will install the Application in the machine. 
The output should be similar to:
```
[ 22%] Built target commons
[ 70%] Built target server
[ 77%] Built target client
[ 81%] Automatic MOC and UIC for target editor
[ 81%] Built target editor_autogen
[100%] Built target editor
Install the project...
-- Install configuration: "Debug"
-- Up-to-date: /usr/local/bin/server
-- Up-to-date: /usr/local/bin/client
-- Installing: /usr/local/lib/libcommons.a
-- Installing: /usr/local/bin/editor

```

### Run
#### Server
The application must be executed with the following syntax: `server [config_file]`
##### Configuration File
The Configuration File has the following format:
```
port=8080
maps_path=resources/maps
units_properties_file_path=resources/config/Game Configuration.json
```
##### Configuration File Parameter
The application accepts the following parameters:
1. `port`: string representing the port to expose.
1. `maps_path`: string representing the path containing all the available maps.
1. `units_properties_file_path`: string representing the path to the [JSON](https://en.wikipedia.org/wiki/JSON) File
with all the game configuration.

#### Client
The application must be executed with the following syntax: `client [host] [port]`
