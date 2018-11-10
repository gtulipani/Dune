#ifndef __CLIENT_H__
#define __CLIENT_H__

// STL Libraries
#include <string>
#include <map>

// Commons Libraries
#include <Socket.h>
#include <Matrix.h>

// Client Libraries
#include "SdlPicturable.h"
#include "Game.h"
#include "../sdl/SdlTexture.h"
#include "../sdl/SdlWindow.h"


using namespace std;

class Client {
private:
    string host;
    string port;

    Socket socket;
    Game game;

    void waitForEvent(std::string message);
public:
    Client(string host, string port);

    void connect();
    void configure();
    void startGame();
};


#endif //__CLIENT_H__
