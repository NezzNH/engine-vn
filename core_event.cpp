#include "core_event.hpp"

CoreEventIndex::CoreEventIndex(std::vector<CoreEventReference> events) {
    this->events = events;
}

bool CoreEventIndex::is_valid_event(CoreEventReference input_event) {
    for (uint8_t i = 0; i < this->events.size(); ++i) {
        if (this->events[i].context_id == input_event.context_id &&
            this->events[i].event_id == input_event.event_id)
                return true;
    }

    return false;
}

void CoreEventIndex::register_event(CoreEventReference input_event) {
    if (this->is_valid_event(input_event)) return;

    this->events.push_back(input_event);
}

std::vector<CoreEventReference> CoreEventIndex::get_all_events() {
    return this->events; //TODO make a simple array
}
