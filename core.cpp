#include "core.hpp"

Core::Core() {

    this->core_data_spaces_limit = 10; //TODO implement a constants system

    core_modules.push_back(Display());
    core_modules.push_back(InputHandler());

    for (size_t i = 0; i < core_modules.size(); ++i)
        core_modules[i].id = 2 + i; //reserve 2 spaces for core messages and system wide messages
    
    core_modules[0].add_sender(core_modules[1].id);
    core_modules[1].add_sender(core_modules[0].id);

    data_spaces.push_back(CoreDataSpace());
}

void Core::start_main_loop() {
    bRunning = true;

    while (this->bRunning) {
        for (int i = 0; i < core_event_queue.size(); ++i) {
            
        }
    }
}