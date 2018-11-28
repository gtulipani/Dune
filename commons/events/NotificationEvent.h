#ifndef __NOTIFICATION_EVENT_H__
#define __NOTIFICATION_EVENT_H__

// STL Libraries
#include <string>

typedef enum NotificationEventType {
    CONNECTION_SUCCESS_EVENT = 0,
    GAME_STARTED_EVENT = 1,
    GAME_CONFIGURATION_EVENT = 2,
    GAME_STATUS_EVENT = 3,
    GAME_LOST = 4,
    GAME_WON = 5
} NotificationEventType;

struct NotificationEvent {
public:
    int message;

    NotificationEvent() = default;

    explicit NotificationEvent(int message);

    NotificationEvent(const NotificationEvent &other);

    NotificationEvent(NotificationEvent &&other) noexcept;

    // Overloading the assignment by copy
    NotificationEvent &operator=(const NotificationEvent &other);

    // Overloading the assignment by movement
    NotificationEvent &operator=(NotificationEvent &&other) noexcept;
};


#endif //__NOTIFICATION_EVENT_H__
