#ifndef CORE_H
#define CORE_H

#include <cstdint>
#include <vector>
#include <deque>

#include "core_module.hpp"
#include "core_state.hpp"
#include "core_event.hpp"
#include "core_event_queue.hpp"
#include "core_data_space.hpp"

#include "display.hpp"
#include "console.hpp"
#include "input_handler.hpp"

class Core {
private:
    bool isRunning;
    CoreStateManager state_manager;
    uint8_t updated_queue; //convert to FIFO for multithreaded support, with associated methods for ease of use

    CoreModuleRegistry core_module_registry;
    std::vector<CoreModule> core_modules;

    std::vector<CoreEventContext> event_contexts;
    std::vector<CoreEventQueue> event_queues;

    uint8_t core_data_spaces_limit;
    std::vector<CoreDataSpace> data_spaces;
public:
    Core();

    Core(std::string);

    void main_loop();
    void route_event(CoreEvent);
    void take_core_event(CoreEvent);
    CoreEvent dispatch_work(uint8_t);

    void register_module(std::string, std::vector<std::string>);

    CoreDataSpace* get_data_space();
    
};

#endif
