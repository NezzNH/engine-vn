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
    uint16_t event_tag;
    uint8_t context;
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

/*struct CoreDataSpaceHeader {
    uint16_t data_size;
    uint8_t data_type;
};*/

/*
struct DialogueEvent : public CoreEvent {
public:
    DialogueEventSignal signal_type;
};

example of how to use this for specific module communication

every single event that inherits from coreevent and thus uses this mechanism
MUST have a signal_type as a field in the derived class

the justficiation is that, even though this field is common with all CoreEvent classes
it's type is not: dialogueevents will have different possible signals to
inputevent signals and so on
*/

/*class CoreDataSpace {
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
};*/

class CoreEventRegistry {
private:
    std::vector<CoreEventContextRegister> contexts;
public:
    CoreEventRegistry();
    CoreEventRegistry(std::vector<CoreModule>);

    void register_new_context(std::string, std::vector<CoreEventRegister>);

    CoreEventContextRegister return_all_contexts();
    CoreEventRegister return_all_events_in_context(uint8_t);
};

class CoreEventQueue {
private:
    std::deque<CoreEvent> event_queue;
    std::vector<uint8_t> associated_contexts;
    uint8_t id;
public:
    CoreEventQueue() = delete;
    CoreEventQueue(uint8_t);

    uint8_t return_id();
};

class Core {
private:
    bool bRunning;
    CoreStateManager state_manager;

    std::vector<CoreModule> core_modules;

    CoreEventRegistry event_registry;
    std::vector<CoreEventQueue> event_queues;

    //uint8_t core_data_spaces_limit;
    //std::vector<CoreDataSpace> data_spaces;
public:
    Core();

    void start_main_loop();
};

#endif
