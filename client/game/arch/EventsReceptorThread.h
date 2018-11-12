#ifndef __EVENTS_RECEPTOR_THREAD_H__
#define __EVENTS_RECEPTOR_THREAD_H__

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
#include "EventsLooperThread.h"
#include "../sdl/SdlTexture.h"
#include "../sdl/SdlWindow.h"


using namespace std;

class EventsReceptorThread : public Thread {
private:
    Socket &socket;
    shaque<GameStatusEvent> &game_status_events;

    void run() override;

    void terminate() override;
public:
    EventsReceptorThread(Socket &socket, shaque<GameStatusEvent> &game_status_events);
};


#endif //__EVENTS_RECEPTOR_THREAD_H__
