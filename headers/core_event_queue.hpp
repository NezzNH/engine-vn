#ifndef CORE_EVENT_QUEUE_H
#define CORE_EVENT_QUEUE_H

#include "core_event.hpp"
#include "core_module.hpp"

#include <vector>
#include <deque>
#include <variant>
#include <cstdint>

struct CoreEventQueueRegister{
    std::vector<std::string> subscribed_events;
    std::vector<CoreModule*> subscribed_modules;
    std::string queue_id;
};

class CoreEventQueue {
private:
    std::vector<CoreModule*> modules; 
    std::vector<std::string> subscribed_events;
    std::deque<std::variant<CoreEvent, CoreDataEvent>> event_queue;
    std::string queue_id;
public:
    CoreEventQueue() = delete;
    CoreEventQueue(std::string);
    std::string return_id();

    void subscribe_to_event(std::string);
    bool is_subscribed_to_event(std::string);

    bool enqueue_event(std::variant<CoreEvent, CoreDataEvent>);

    CoreEvent hand_off_event_sync();
    CoreDataEvent hand_off_event_sync();
};

#endif
