#include "core.hpp"

Core::Core(std::string state_name) {
    this->state_manager = CoreStateManager(state_name);
}

void Core::main_loop() {
    while (this->isRunning) {
        
    }
}

