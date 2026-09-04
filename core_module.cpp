#include "core_module.hpp"

void CoreModule::activate_module() {
    this->isListening = true;
}

void CoreModule::deactivate_module() {
    this->isListening = false;
}

bool CoreModule::is_active() {
    return this->isListening;
}

bool CoreModule::is_subscribed_to_event(std::string event_id) {
    for (uint16_t i = 0; i < this->events.size(); ++i)
        if (event_id == this->events[i])
            return true;

    return false;
}

bool CoreModule::is_subscribed_to_event(CoreEvent event) {
    return this->is_subscribed_to_event(event.event_id);
}

bool CoreModule::is_subscribed_to_event(CoreDataEvent event) {
    return this->is_subscribed_to_event(event.event_id);
}

bool CoreModule::is_busy() {
    return this->is_busy;
}

std::vector<std::string> CoreModule::get_events() {
    return this->events;
}
