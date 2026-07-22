#include "core.hpp"

Core::Core() {

}

void Core::route_event(CoreEvent input_event) {

    if (input_event.context == 0) this->take_core_event(input_event);

    if (!(this->event_registry.contains_event(input_event)))  {
       this->take_core_event({{5},{0},{0},{0}});
       return;
    }
    else {
        for (uint8_t i = 0; i < this->event_queues.size(); ++i) {
            if (this->event_queues[i].is_subscribed_to_event(input_event)) {
                this->event_queues[i].enqueue_event(input_event);
                this->updated_queue = i;
                return;
            }
        }
    }

    //this->take_core_event(null_event_copy);

}

bool CoreEventQueue::enqueue_event(CoreEvent input_event) {

    for (uint8_t i = 0; i < this->subscribed_events.size(); ++i) {
        this->event_queue.push_front(input_event);
        return true;
    }

    return false;

}

CoreEvent CoreEventQueue::hand_off_control_flow() {
    
    for (uint8_t i = 0; i < this->modules.size(); ++i)
        if (this->modules[i]->isSubscribedToEvent(this->event_queue.front())) {
           return this->modules[i]->hand_off_control_flow(this->event_queue.front());
        }
    return {};
}

CoreEvent Core::dispatch_work(uint8_t queue_id) {
    return this->event_queues[queue_id].hand_off_control_flow();
}

void Core::main_loop() {

    CoreEvent current_event; //TODO goes without saying, this will have to be a better return method later on
    while (this->bRunning) {
        this->route_event(current_event);
        current_event = this->dispatch_work(this->updated_queue);
    }
}

CoreEventRegistry::CoreEventRegistry(uint8_t context_id, std::string context_name, std::string context_description) {
    CoreEventContext context;
    context.id = context_id;
    this->context_registers.push_back({{context}, {}, {context_name}, {context_description}});
}

void CoreEventRegistry::register_new_event(uint8_t event_id, uint8_t context_id, std::string event_name, std::string event_description) {
    if (!(this->contains_context(context_id))) return; //TODO return error by pushing to core

    uint8_t context_index;

    for (int i = 0; i < this->context_registers.size(); ++i) {
        if (context_id == context_registers[i].context.id) {
            context_index = i;
            break;
        }
    }

    this->context_registers[context_index].context.events.push_back({{},{},{},{}});
    this->context


}