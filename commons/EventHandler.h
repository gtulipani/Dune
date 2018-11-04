#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "Event.h"

class Socket;

class EventHandler {
public:
    static void sendEvent(const Socket &socket, const Event &event);

    static Event receiveEvent(const Socket &socket);
};


#endif //__EVENT_HANDLER_H__
