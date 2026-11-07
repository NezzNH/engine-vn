#include "integer_iterator.hpp"

#include <array>
#include <iostream>

static constexpr std::array incoming_events_decl {
    std::string_view{"counter;update"}
};

static constexpr std::array outgoing_events_decl {
    std::string_view{"counter;updated"}
};

CoreModule::CoreModule() {
    this->incoming_events.insert(incoming_events.end(), 
                            incoming_events_decl.begin(),
                            incoming_events_decl.end());
    
    this->outgoing_events.insert(outgoing_events.end(), 
                            outgoing_events_decl.begin(),
                            outgoing_events_decl.end());

    std::cout << "hello im the derived constructor\n";
}