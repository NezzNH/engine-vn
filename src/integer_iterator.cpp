#include "integer_iterator.hpp"

#include <array>
#include <iostream>

std::array incoming_events_decl {
    std::string{"integer_iterator;update"}
};

std::array outgoing_events_decl {
    std::string{"integer_iterator;updated"}
};

IntegerIterator::IntegerIterator() {
    for (uint16_t i = 0; i < incoming_events_decl.size(); ++i)
        this->add_incoming_event_subscription(incoming_events_decl[i]);

    for (uint16_t i = 0; i < outgoing_events_decl.size(); ++i)
        this->add_outgoing_event_subscription(outgoing_events_decl[i]);
}

void IntegerIterator::integer_increment() {this->the_integer++;}

CoreEvent IntegerIterator::hand_off_event_sync(CoreEvent event) {
    if (event.event_id == "update") {
        this->integer_increment();
        return {"integer_iterator","updated"};
    }
    else
        return {"core","blank"};
}

CoreEvent IntegerIterator::hand_off_event_sync(CoreDataEvent event) {
    return this->hand_off_event_sync(CoreEvent{event.context_id, event.event_id});
}