#include "integer_iterator.hpp"

#include <array>
#include <iostream>

std::array incoming_events_decl {
    std::string{"counter;update"}
};

std::array outgoing_events_decl {
    std::string{"counter;updated"}
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