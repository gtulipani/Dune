#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "ClientEvent.h"
#include "GameStatusEvent.h"
#include "MapConfigurationEvent.h"
#include "NotificationEvent.h"

class Socket;

class EventHandler {
public:
    static void sendEvent(const Socket &socket, const ClientEvent &event);
    static void sendEvent(const Socket &socket, const MapConfigurationEvent &event);
    static void sendEvent(const Socket &socket, const GameStatusEvent &event);
    static void sendEvent(const Socket &socket, const NotificationEvent &event);

    static ClientEvent receiveEvent(const Socket &socket);
    static MapConfigurationEvent receiveMapConfigurationEvent(const Socket &socket);
    static GameStatusEvent receiveGameStatusEvent(const Socket &socket);
    static NotificationEvent receiveNotificationEvent(const Socket &socket);
};


#endif //__EVENT_HANDLER_H__
