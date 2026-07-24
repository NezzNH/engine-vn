#ifndef CORE_EVENT_QUEUE_H
#define CORE_EVENT_QUEUE_H

#include "core_event.hpp"
#include "core_module.hpp"

#include <vector>
#include <deque>
#include <cstdint>

struct CoreEventQueueRegister{
    std::vector<CoreEventRegister> subscribed_events;
    std::vector<CoreModule*> subscribed_modules;
    uint8_t queue_id;
};

class CoreEventQueue {
private:
    std::vector<CoreModule*> modules; 
    std::vector<CoreEventReference> subscribed_events;
    std::deque<CoreEvent> event_queue;
    uint8_t queue_id;
public:
    CoreEventQueue() = delete;
    CoreEventQueue(uint8_t);
    uint8_t return_id();

    void subscribe_to_event(CoreEvent);
    bool is_subscribed_to_event(CoreEvent);

    bool enqueue_event(CoreEvent);

    CoreEvent hand_off_control_flow();
};

#endif