#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "core_module.hpp"
#include "core_event.hpp"
#include "core_event_queue.hpp"

#include <map>
#include <cstdint>
#include <string>
#include <stack>
#include <vector>
#include <array>

struct CoreState {
    CoreModuleRegistry modules;
    CoreEventQueueIndex event_queues;
    std::string name;
    uint8_t state_id;
};

struct CoreStateRegister {
    uint8_t state_id;
    std::string name, description;
};

class CoreStateRegistry{
private:
    std::vector<CoreStateRegister> registers;
public:
    CoreStateRegistry();

    uint8_t get_id_from_name(std::string);
};

class CoreStateManager {
private:
    std::stack<CoreState> game_state_stack;
    CoreStateGraph graph;

    void standard_initialization(); //this is just for now, the states should be loaded dynamically
public:
    CoreStateManager();

    CoreStateManager(std::string);

    CoreState request_change_game_state(CoreEvent);
    CoreState curr_game_state;
};

struct CoreStateGraphNode {
    CoreState node_state;
    std::vector<uint8_t> neighbors;
};

class CoreStateGraph {
private:
    std::vector<CoreStateGraphNode> nodes;
    uint8_t current_index;
public:
    CoreStateGraph();
    CoreState curr_core_state();
    CoreState change_core_state(std::uint8_t);
    void update_index(); //this would be if the game manager stack changes the state instead of the graph
};

#endif