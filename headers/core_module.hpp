#ifndef CORE_MODULE_H
#define CORE_MODULE_H

#include <vector>

#include "core_event.hpp"
#include "core_data_space.hpp"

struct CoreModuleRegister{
    std::vector<std::string> module_incoming_events;
    std::vector<std::string> module_outgoing_events;
    std::string name, description;
};

class CoreModuleRegistry {
private:
    std::vector<CoreModuleRegister> module_registers;
public:
    CoreModuleRegistry();
    
    bool contains_module_register(std::string);
    void register_module(std::string, std::vector<std::string>);
};

class CoreModule {
private:
    std::string module_id;

    CoreDataSpace* data_space_p;
    std::vector<CoreDataSpaceHeader> data_space_headers;

    std::vector<CoreEventContextIndex> incoming_events;
    std::vector<CoreEventContextIndex> outgoing_events;
    
    bool b_is_busy; //TODO async fields
public:
    CoreModule();
    CoreModule(std::string);
    CoreModule(std::string, CoreDataSpace*);

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

    std::vector<std::string> get_incoming_events();
    std::vector<std::string> get_outgoing_events();
};

#endif