#ifndef CORE_MODULE_H
#define CORE_MODULE_H

#include <cstdint>
#include <deque>
#include <vector>

#include "core.hpp"

class CoreModule {
private:
    std::deque<CoreEvent> internal_event_queue;
    bool bIsDoingSomething, hasEventsQueued; 
    //intended to be an indicator of multithreaded behavior
public:
    uint8_t id;

    CoreEvent hand_off_control_flow();
    //NOTE this is a very rudementary return mechanism, and will
    //generally not work for async modules who do not get control flow

    //TODO async methods
    void push_event();
    void hand_off_event(CoreEvent);
    bool isDoingSomething();

    bool isARecipientOfMessageFrom(uint8_t);

    CoreModule();
};

#endif
