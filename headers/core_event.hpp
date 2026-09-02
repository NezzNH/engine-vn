#ifndef CORE_EVENT_H
#define CORE_EVENT_H

#include <cstdint>
#include <vector>
#include <string>

struct CoreEvent {
    std::string context_id, event_id;
};

struct CoreDataEvent : CoreEvent {
    std::string data_header_id, data_id;
};

/*class CoreEventIndex {
private:
    std::vector<CoreEventReference> events;
public:
    CoreEventIndex();
    CoreEventIndex(std::vector<CoreEventReference>);

    bool is_valid_event(CoreEventReference);
    
    void register_event(CoreEventReference);
    std::vector<CoreEventReference> get_all_events();
};*/

struct CoreEventRegister {
    CoreEvent event;
    std::string description;
    uint16_t numerical_id;
};

class CoreEventContext {
private:
    std::vector<CoreEventRegister> events;
    std::string context_name;
    uint16_t context_numerical_id;

    bool event_already_registered(std::string);
public:
    CoreEventContext();
    ~CoreEventContext();

    bool register_event(std::string);
    bool register_event(std::string, std::string);

    void delete_event(std::string);
};

#endif
