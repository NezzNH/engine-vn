#ifndef CORE_EVENT_H
#define CORE_EVENT_H

#include <cstdint>
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

class CoreEventContext {
private:
    std::vector<CoreEventRegister> events;
    std::string context_name;

    bool event_already_registered(std::string);
public:
    CoreEventContext();
    ~CoreEventContext();

    bool register_event(std::string);
    bool register_event(std::string, std::string);

    void delete_event(std::string);
};

#endif
