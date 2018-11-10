#ifndef __GAME_H__
#define __GAME_H__

// Commons Libraries
#include <Socket.h>

// Client libraries
#include "MainWindow.h"

union SDL_Event;

class Game {
private:
    Socket socket;
    MainWindow main_window;

    void sendEvent(std::string message, Point position);

    void processMouseEvent(SDL_Event& event);
    void processKeyDownEvent(SDL_Event& event);
    void processEventFromSocket();
    Matrix receiveMatrix();
public:
    Game() = default;

    void configure(Socket socket);
    void start();
};


#endif //__GAME_H__
