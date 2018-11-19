#ifndef __NOTIFICATION_EVENT_H__
#define __NOTIFICATION_EVENT_H__

#include <string>

#ifndef __EVENT_TYPES__
#define __EVENT_TYPES__

// Define the types of events
#define CONNECTION_SUCCESS_EVENT "CONNECTION_SUCCESS"
#define GAME_STARTED_EVENT "GAME_STARTED"
#define GAME_CONFIGURATION_EVENT "GAME_CONFIGURATION"
#define GAME_STATUS_EVENT "GAME_STATUS"

#endif

struct NotificationEvent {
public:
    std::string message;

    NotificationEvent() = default;

    explicit NotificationEvent(std::string message);

    NotificationEvent(const NotificationEvent &other);

    NotificationEvent(NotificationEvent &&other) noexcept;

    // Overloading the assignment by copy
    NotificationEvent &operator=(const NotificationEvent &other);

    // Overloading the assignment by movement
    NotificationEvent &operator=(NotificationEvent &&other) noexcept;
};


#endif //__NOTIFICATION_EVENT_H__
