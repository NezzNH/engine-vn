#include "core_state.hpp"

void CoreStateManager::standard_initialization() {
    this->graph = CoreStateGraph();
}

CoreStateGraph::CoreStateGraph() {

    //again, this will all be done dynamically later on

    CoreStateGraphNode temp_node;
    CoreState temp_state;
    std::vector<uint8_t> temp_neighbors;
    CoreEventQueueRegister temp_queue_register;

    //Main Menu
    
}

CoreStateManager::CoreStateManager() {
    this->standard_initialization();
}

CoreStateManager::CoreStateManager(std::string starting_state_name) {
    this->standard_initialization();

    
}

inline CoreState CoreStateGraph::curr_core_state() {return this->nodes[current_index].node_state;}