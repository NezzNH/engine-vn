#include "core_state.hpp"

MainMenu::MainMenu() {
    this->display_string = "MAIN MENU";
}

OptionsMenu::OptionsMenu() {
    this->display_string = "OPTIONS MENU";
}

CreditsMenu::CreditsMenu() {
    this->display_string = "CREDITS MENU";
}

GameplayLoop::GameplayLoop() {
    this->display_string = "GAMEPLAY LOOP";
}

Exit::Exit() {
    this->display_string = "Closing...";
}

CoreStateManager::CoreStateManager() {
    this->graph = CoreStateGraph();
    this->game_state_stack.push(Exit());
    this->game_state_stack.push(MainMenu());

    this->curr_game_state = this->graph.curr_core_state();
}

CoreStateGraph::CoreStateGraph() {
    CoreStateGraphNode root_node, exit_node;

    this->total_states = 2;
    this->current_index = 1;

    root_node.node_state = MainMenu();
    root_node.neighbors.push_back(0);
    root_node.change_signal.push_back({0x51});

    this->nodes[1] = root_node;

    exit_node.node_state = Exit();
    exit_node.change_signal.push_back({});

    this->nodes[0] = exit_node;
}

inline CoreState CoreStateGraph::curr_core_state() {return this->nodes[current_index].node_state;}