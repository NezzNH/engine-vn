#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <map>
#include <cstdint>
#include <string>
#include <stack>
#include <vector>
#include <array>

struct CoreStateSignal {
    uint32_t scan_code; 
};

class CoreState {
public:
    std::string display_string;
};

class MainMenu : public CoreState {
public:
    MainMenu();
};

class OptionsMenu : public CoreState {
public:
    OptionsMenu();
};

class CreditsMenu : public CoreState {
public:
    CreditsMenu();
};

class GameplayLoop : public CoreState {
public:
    GameplayLoop();
};

class Exit : public CoreState {
public:
    Exit();
};

class CoreStateManager {
private:
    std::stack<CoreState> game_state_stack;
    CoreStateGraph graph;
public:
    CoreStateManager();

    CoreState request_change_game_state(CoreStateSignal);
    CoreState curr_game_state;
};

struct CoreStateGraphNode {
    CoreState node_state;
    std::vector<uint8_t> neighbors;
    std::vector<CoreStateSignal> change_signal;
};

class CoreStateGraph {
private:
    std::array<CoreStateGraphNode, 10> nodes;
    uint8_t total_states, current_index;
public:
    CoreStateGraph();
    CoreState curr_core_state();
    CoreState change_core_state(std::uint8_t);
    void update_index(); //this would be if the game manager stack changes the state instead of the graph
};

#endif