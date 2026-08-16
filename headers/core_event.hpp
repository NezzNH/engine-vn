#ifndef CORE_EVENT_H
#define CORE_EVENT_H

#include <cstdint>
#include <vector>
#include <string>

struct CoreDataEvent {
    std::string context_id, event_id;
    std::string data_header_id, data_id;
};

struct CoreEvent {
    std::string context_id, event_id;
};

class CoreEventIndex {
private:
    std::vector<CoreEventReference> events;
public:
    CoreEventIndex();
    CoreEventIndex(std::vector<CoreEventReference>);

    bool is_valid_event(CoreEventReference);
    
    void register_event(CoreEventReference);
    std::vector<CoreEventReference> get_all_events();
};

struct CoreEventContext {
    CoreEventIndex events;
    std::string id;
};

struct CoreEventRegister {
    std::string name, description;
    CoreEventReference event;
};

struct CoreEventContextRegister {
    std::vector<CoreEventRegister> event_registers;
    std::string name, description;
    std::string context_id;
};

class CoreEventRegistry {
private:
    std::vector<CoreEventContextRegister> context_registers;
public:
    void add_events(CoreEventIndex);
    void add_events(CoreEventContextRegister); //TODO build this from each module, send it that way. adds descriptions and so on

    uint8_t get_next_available_context_id();
};

#endif
