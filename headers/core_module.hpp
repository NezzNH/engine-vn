#ifndef CORE_MODULE_H
#define CORE_MODULE_H

#include <cstdint>
#include <deque>
#include <vector>
#include <array>

#include "core.hpp"

struct CoreModuleRegister {
    std::string name, description;
    
};

class CoreModule {
private:
    bool bIsDoingSomething; 
    std::vector<uint8_t> core_event_contexts;
    //intended to be an indicator of multithreaded behavior
public:
    uint8_t id;

    virtual CoreEvent hand_off_control_flow(CoreEvent) = 0;
    //NOTE this is a very rudementary return mechanism, and will
    //generally not work for async modules who do not get control flow
    //of the main thread

    //TODO async methods
    void push_event();
    virtual void hand_off_event(CoreEvent) = 0;
    bool isDoingSomething();

    CoreModule();
};

#endif
