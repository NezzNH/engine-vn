#include "core_event.hpp"

CoreEventContext::CoreEventContext() {
    this->context_name = "default_context";
    this->context_numerical_id = 0;
}

CoreEventContext::~CoreEventContext() {
    this->events.clear();
}

bool CoreEventContext::event_already_registered(std::string event_id) {
    for (uint16_t i = 0; i < this->event.size(); ++i)
        if (this->events[i].event.event_id == event_id) 
            return false;
    return true;
}

bool CoreEventContext::register_event(std::string event_id) {

    if (this->event_already_registered(event_id)) return false;

    this->events.push_back({{this->context_name, event_id}, "", 0});

    return true;
}

bool CoreEventContext::register_event(std::string event_id, std::string description) {
    if (this->event_already_registered(event_id)) return false;

    this->events.push_back({{this->context_name, event_id}, description, 0});

    return true;
}

void CoreEventContext::delete_event(std::string event_id) {
    for (uint8_t i = 0; i < this->events.size(); ++i) {
        if (this->events[i].event.event_id == event_id) {
            this->events.erase(i);
            break;
        }
    }
}
