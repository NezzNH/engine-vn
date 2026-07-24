#ifndef CORE_MODULE_H
#define CORE_MODULE_H

#include <cstdint>
#include <deque>
#include <vector>
#include <array>

#include "core_event.hpp"
#include "core_data_space.hpp"

struct CoreModuleRegister{
    CoreEventRegistry module_events;
    std::string name, description;
    uint8_t module_type_id;
};

class CoreModuleRegistry {
private:
    std::vector<CoreModuleRegister> module_registers;
public:
    CoreModuleRegistry();
};

class CoreModule {
private:
    uint8_t module_id, module_type_id;

    CoreEventIndex event_index;
    
    bool isDoingSomething; //TODO async fields
    bool isListening; //will be unified with bIsDoingSomething, but for now this is different from if the module is doing anything
public:

    CoreModule() = delete;
    CoreModule(uint8_t);

    bool isSubscribedToEvent(CoreEventReference);
    bool isSubscribedToEvent(CoreEvent);

    bool isActive();
    void activate_module();
    void deactivate_module();

    virtual CoreEvent hand_off_control_flow(CoreEvent) = 0;

    //TODO async methods
    virtual void hand_off_event(CoreEvent) = 0;
    bool isDoingSomething();

    CoreModule();

    CoreEventIndex get_event_index();
};

#endif
