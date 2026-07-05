#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <map>
#include <cstdint>
#include <string>
#include <stack>
#include <vector>
#include <array>

struct GameStateSignal {
    uint32_t scan_code; 
};

class GameState {
public:
    std::string display_string;
};

class MainMenu : public GameState {
public:
    MainMenu();
};

class OptionsMenu : public GameState {
public:
    OptionsMenu();
};

class CreditsMenu : public GameState {
public:
    CreditsMenu();
};

class GameplayLoop : public GameState {
public:
    GameplayLoop();
};

class Exit : public GameState {
public:
    Exit();
};

class GameStateManager {
private:
    std::stack<GameState> game_state_stack;
    GameStateGraph graph;
public:
    GameStateManager();

    GameState request_change_game_state(GameStateSignal);
    GameState curr_game_state;
};

struct GameStateGraphNode {
    GameState node_state;
    std::vector<uint8_t> neighbors;
    std::vector<GameStateSignal> change_signal;
};

class GameStateGraph {
private:
    std::array<GameStateGraphNode, 10> nodes;
    uint8_t total_states, current_index;
public:
    GameStateGraph();
    GameState curr_game_state();
    GameState change_game_state(std::uint8_t);
    void update_index(); //this would be if the game manager stack changes the state instead of the graph
};

#endif