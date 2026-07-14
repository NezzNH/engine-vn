#ifndef CORE_H
#define CORE_H

#include <cstdint>
#include <vector>
#include <deque>

#include "core_module.hpp"

#include "display.hpp"
#include "console.hpp"
#include "input_handler.hpp"

enum class CoreEventType : uint8_t {
    MODULE_MESSAGE,
    DATA_SPACE_UPDATE
};

struct CoreEvent {
    uint8_t sender_id, recipient_id;
    CoreEventType type;
};

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

class CoreDataSpace {
private:
    std::vector<uint8_t> raw_data;
    std::vector<uint8_t> participants;
public:
    CoreDataSpace();
    CoreDataSpace(uint8_t*, uint8_t);
    CoreDataSpace(uint8_t*, uint8_t, uint8_t*, uint8_t);
    CoreDataSpace(uint8_t*, uint8_t);

    void add_participant(uint8_t);

    void set_data(std::vector<uint8_t>);
    void set_data(uint8_t*, uint8_t);
    void append_data(std::vector<uint8_t>);
    void append_data(uint8_t*, uint8_t);
};

class Core {
private:
    std::deque<CoreEvent> core_event_queue;
    std::vector<CoreDataSpace> data_spaces;
    std::vector<CoreModule> core_modules;
    uint8_t core_data_spaces_limit;
    bool bRunning;
public:
    bool enqueue_event();
    void start_main_loop();
};

#endif