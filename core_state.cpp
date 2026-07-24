#include "core_state.hpp"

CoreStateManager::CoreStateManager() {
    
}

inline CoreState CoreStateGraph::curr_core_state() {return this->nodes[current_index].node_state;}