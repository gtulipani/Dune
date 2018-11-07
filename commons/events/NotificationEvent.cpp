#include "NotificationEvent.h"

NotificationEvent::NotificationEvent(std::string message) :
        message(std::move(message)) {}

NotificationEvent::NotificationEvent(const NotificationEvent &other) : NotificationEvent(
        other.message) {}

NotificationEvent::NotificationEvent(NotificationEvent &&other) noexcept : NotificationEvent(
        std::move(other.message)) {}

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
    this->message = std::move(other.message);

    return *this;
}
