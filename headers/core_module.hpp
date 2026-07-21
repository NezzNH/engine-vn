#ifndef CORE_MODULE_H
#define CORE_MODULE_H

#include <cstdint>
#include <deque>
#include <vector>
#include <array>

#include "core.hpp"

struct CoreModuleRegister{
    CoreEventRegistry associated_contexts;
    std::string name, description;
    uint8_t module_id;
};

class CoreModule {
private:
    bool bIsDoingSomething; //TODO async fields

    CoreEventRegistry event_registry;
public:
    uint8_t module_id;

    bool isSubscribedToEvent(CoreEvent);

    virtual CoreEvent hand_off_control_flow(CoreEvent) = 0;

    //TODO async methods
    virtual void hand_off_event(CoreEvent) = 0;
    bool isDoingSomething();

    CoreModule();

    CoreEventRegistry get_event_registry();
};

#endif
