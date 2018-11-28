#include "NotificationEvent.h"

NotificationEvent::NotificationEvent(int message) :
        message(message) {}

NotificationEvent::NotificationEvent(const NotificationEvent &other) : NotificationEvent(
        other.message) {}

NotificationEvent::NotificationEvent(NotificationEvent &&other) noexcept : NotificationEvent(
        other.message) {
    other.message = -1;
}

NotificationEvent &NotificationEvent::operator=(const NotificationEvent &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->message = other.message;

    return *this;
}

NotificationEvent &NotificationEvent::operator=(NotificationEvent &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->message = other.message;

    other.message = -1;

    return *this;
}
