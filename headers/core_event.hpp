#ifndef CORE_EVENT_H
#define CORE_EVENT_H

#include <cstdint>
#include <vector>
#include <string>

struct CoreEvent {
    uint16_t event_id, data_header_id;
    uint8_t context_id, data_id;
};

struct CoreEventReference {
    uint16_t event_id;
    uint8_t context_id;
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
    uint8_t id;
};

struct CoreEventRegister {
    std::string name, description;
    CoreEventReference event;
};

struct CoreEventContextRegister {
    std::vector<CoreEventRegister> event_registers;
    std::string name, description;
    uint8_t context_id;
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