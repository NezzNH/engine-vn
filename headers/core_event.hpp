#ifndef CORE_EVENT_H
#define CORE_EVENT_H

#include <vector>
#include <string>

struct CoreEvent {
    std::string context_id, event_id;
};

struct CoreDataEvent : CoreEvent {
    std::string data_section_id, data_type_id;
};

struct CoreEventRegister {
    CoreEvent event;
    std::string description;
};

struct CoreEventContext {
    std::vector<CoreEvent> event;
    std::string context_id;
};

struct CoreEventContextIndex {
    std::vector<std::string> event_ids;
    std::string context_id;
};

std::string get_context_of_event(std::string);
std::string get_name_of_event(std::string);

#endif