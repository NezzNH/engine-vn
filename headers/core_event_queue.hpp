#ifndef CORE_EVENT_QUEUE_H
#define CORE_EVENT_QUEUE_H

#include "core_event.hpp"
#include "core_module.hpp"

#include <vector>
#include <deque>
#include <cstdint>

class CoreEventQueue {
private:
    std::vector<CoreModule*> modules; 
    std::vector<CoreEvent> subscribed_events;
    std::deque<CoreEvent> event_queue;
    //Core* core_ref; this is most likely not necessary
    uint8_t id;
public:
    CoreEventQueue() = delete;
    CoreEventQueue(uint8_t);
    uint8_t return_id();

    void subscribe_to_event(CoreEvent);
    void subscribe_to_events(std::vector<CoreEvent>);
    bool is_subscribed_to_event(CoreEvent);

    bool enqueue_event(CoreEvent);

    CoreEvent hand_off_control_flow();
};

#endif