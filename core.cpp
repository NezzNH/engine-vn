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

