#ifndef __CLIENT_H__
#define __CLIENT_H__

// STL Libraries
#include <string>
#include <map>

// Commons Libraries
#include <Socket.h>
#include <Matrix.h>

// Client Libraries
#include "SdlTexture.h"
#include "SdlWindow.h"
#include "SdlPicturable.h"

using namespace std;

class Client {
private:
    string host;
    string port;
    bool game_started;

    int width;
    int height;
    Socket socket;
    Matrix matrix;
    SdlWindow window;
    std::map<int, SdlTexture&> terrain_render_map;
    std::vector<SdlPicturable> picturables;

    void getEvent();
    void waitForGameStart();
public:
    Client(string host, string port);

    void start();
};


#endif //__CLIENT_H__
