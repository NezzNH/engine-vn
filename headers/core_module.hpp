#ifndef CORE_MODULE_H
#define CORE_MODULE_H

#include <cstdint>
#include <deque>
#include <vector>
#include <array>

#include "core_event.hpp"
#include "core_data_space.hpp"

struct CoreModuleRegister{
    std::vector<std::string> module_events;
    std::string name, description;
};

class CoreModuleRegistry {
private:
    std::vector<CoreModuleRegister> module_registers;
public:
    CoreModuleRegistry();
};

class CoreModule {
private:
    std::string module_id;

    CoreDataSpace* data_space_p;
    std::vector<CoreDataSpaceHeader> data_space_headers;

    std::vector<std::string> events;

    bool is_busy; //TODO async fields
    bool is_listening; //will be unified with bIsDoingSomething, but for now this is different from if the module is doing anything
public:

    CoreModule() = delete;
    CoreModule(uint8_t);

    bool is_subscribed_to_event(std::string);
    bool is_subscribed_to_event(CoreEvent);
    bool is_subscribed_to_event(CoreDataEvent);

    bool is_active();
    void activate_module();
    void deactivate_module();

    virtual CoreEvent hand_off_event_sync(CoreEvent) = 0;
    virtual CoreEvent hand_off_event_sync(CoreDataEvent) = 0;

    //TODO async methods
    virtual void hand_off_event_async(CoreEvent) = 0;
    virtual void hand_off_event_async(CoreDataEvent) = 0;
    bool is_busy();

    CoreModule();
    std::vector<std::string> get_events();
};

#endif
