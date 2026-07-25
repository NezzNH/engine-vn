#include "core_event_queue.hpp"

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

void CoreEventQueueIndex::add_queue_index(CoreEventQueueRegister queue_register) {
    if (this->contains_register(queue_register)) return; //TODO add error handling

    this->registers.push_back(queue_register);
}

std::vector<CoreEventQueueRegister> CoreEventQueueIndex::get_registers() {
    return this->registers;
}
