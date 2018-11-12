#ifndef __CLIENT__THREAD_H__
#define __CLIENT__THREAD_H__

// STL Libraries
#include <string>
#include <map>

// Commons Libraries
#include <Socket.h>
#include <Matrix.h>
#include <Thread.h>
#include <shaque.h>
#include <events/ClientEvent.h>

// Client Libraries
#include "SdlPicturable.h"
#include "GameThread.h"
#include "../sdl/SdlTexture.h"
#include "../sdl/SdlWindow.h"


using namespace std;

class ClientThread : public Thread {
private:
    string host;
    string port;
    std::mutex game_status_mutex;
    std::mutex output_messages_mutex;
    shaque<GameStatusEvent> game_status_events;
    shaque<ClientEvent> output_messages;
    GameThread game_thread;

    Socket socket;

    void run() override;

    void terminate() override;

    void waitForEvent(std::string message);

    Matrix receiveTerrainMatrix();

    void fetchServerEvents();

    void sendClientEvents();

    void processEvents();
public:
    ClientThread(string host, string port);

    void connect();
    void configure();
};


#endif //__CLIENT__THREAD_H__
