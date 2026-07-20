#ifndef CORE_H
#define CORE_H

#include <cstdint>
#include <vector>
#include <deque>

#include "core_module.hpp"
#include "core_state.hpp"

#include "display.hpp"
#include "console.hpp"
#include "input_handler.hpp"

struct CoreEvent {
    uint16_t event_id, dataspace_header_id;
    uint8_t context, dataspace_id;
};

struct CoreEventRegister {
    std::string name, description;
    CoreEvent event;
};

struct CoreEventContextRegister {
    std::vector<CoreEventRegister> events;
    std::string name, description;
    uint8_t context_id;
};

struct CoreDataSpaceHeader {
    uint16_t data_size;
    uint8_t data_type;
};

class CoreDataSpace {
private:
    std::vector<CoreDataSpaceHeader> headers;
    std::vector<uint8_t> data;
public:
    CoreDataSpace();

    bool is_empty();
    void clear();

    bool add_record(CoreDataSpaceHeader, uint8_t*);
    bool add_record(CoreDataSpaceHeader, std::vector<uint8_t>);

    bool pop_record(uint8_t);
};

class CoreEventRegistry {
private:
    std::vector<CoreEventContextRegister> contexts;
public:
    CoreEventRegistry();
    CoreEventRegistry(std::vector<CoreModule>);

    void register_new_context(std::string, std::vector<CoreEventRegister>);
    void register_new_event(uint8_t, CoreEvent);

    bool contains_event(CoreEvent);
    bool contains_context(CoreEventContextRegister);

    std::vector<CoreEventRegister> return_all_events();

    CoreEventContextRegister return_all_contexts();
    CoreEventRegister return_all_events_in_context(uint8_t);
};

class CoreEventQueue {
private:
    std::vector<CoreModule*> modules; 
    std::vector<CoreEvent> subscribed_events;
    std::deque<CoreEvent> event_queue;
    Core* core_ref;
    uint8_t id;
public:
    CoreEventQueue() = delete;
    CoreEventQueue(uint8_t);
    uint8_t return_id();

    void subscribe_to_event(CoreEvent);
    void subscribe_to_events(std::vector<CoreEvent>);
    bool is_subscribed_to_event(CoreEvent);

    bool enqueue_event(CoreEvent);

    bool hand_off_control_flow();
};

class CoreModuleRegistry {
private:
    std::vector<CoreModuleRegister> module_registers;
public:
    CoreModuleRegistry();
    CoreModuleRegistry();
};

class Core {
private:
    bool bRunning;
    CoreStateManager state_manager;
    uint8_t updated_queue;

    CoreModuleRegistry core_module_registry;
    std::vector<CoreModule> core_modules;

    CoreEventRegistry event_registry;
    std::vector<CoreEventQueue> event_queues;

    //uint8_t core_data_spaces_limit;
    //std::vector<CoreDataSpace> data_spaces;
public:
    Core();

    void main_loop();
    void route_event(CoreEvent);
    void take_core_event(CoreEvent);
    void dispatch_work();
};

#endif
