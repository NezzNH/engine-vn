#include "core_module.hpp"

void CoreModule::activate_module() {
    this->isListening = true;
}

void CoreModule::deactivate_module() {
    this->isListening = false;
}

bool CoreModule::isActive() {
    return this->isListening;
}

bool CoreModule::isSubscribedToEvent(CoreEventReference input_event_ref) {
    return this->event_index.is_valid_event(input_event_ref);
}

bool CoreModule::isSubscribedToEvent(CoreEvent input_event) {
    CoreEventReference ref = {{input_event.event_id},{input_event.context_id}};
    return this->isSubscribedToEvent(ref);
}