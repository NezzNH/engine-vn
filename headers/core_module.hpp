#ifndef CORE_MODULE_H
#define CORE_MODULE_H

#include <cstdint>
#include <deque>
#include <vector>

#include "core.hpp"

class CoreModule {
private:
    std::deque<CoreEvent> internal_event_queue;
    std::vector<uint8_t> senders;
    bool bIsDoingSomething, hasEventsQueued; 
    //intended to be an indicator of multithreaded behavior
public:
    uint8_t id;

    bool isDoingSomething();
    void hand_off_event(CoreEvent);

    void add_sender(uint8_t);
    void add_senders(uint8_t*, uint8_t);
    void add_senders(std::vector<uint8_t>);

    void remove_sender(uint8_t);
    void remove_senders(uint8_t*, uint8_t);
    void remove_senders(std::vector<uint8_t>);

    bool isARecipientOfMessageFrom(uint8_t);

    CoreModule();
};

#endif