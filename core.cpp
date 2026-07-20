#include "core.hpp"

CoreEvent null_event_copy = {{0}, {0}, {0}, {0}};

CoreEventRegistry::CoreEventRegistry() {
    this->contexts.push_back({
        {
            {
                {
                    "null_event"
                },
                {
                    "Is emmited whenever an event couldn't be emmited."
                },
                {
                    {0}, {0}
                }
            },
            {
                {
                    "force_shutdown"
                },
                {
                    "Quits the entire program immediately without any exit procedure. Loses all data."
                },
                {
                    {1}, {0}
                }
            },
            {
                {
                    "change_state"
                },
                {
                    "Makes the core change program states, constructing new modules where necessary."
                },
                {
                    {2}, {0}
                }
            },
            {
                {
                    "create_data_space"
                },
                {
                    "Creates an empty data space with 0 sections."
                },
                {
                    {3}, {0}
                }
            },
            {
                {
                    "unhandled_event_warning"
                },
                {
                    "Is emmited by the core after an event has looked through all possible modules in the queue and not found a recipient."
                },
                {
                    {4}, {0}
                }
            }
        },
        "CoreEvents",
        "Events used to signal broad program changes to the core or system specific requests",
        0
    });

//TODO this goes without saying, but all of this should be moved externally to a file.
//if it quacks like a JSON and walks like a JSON...
//shove it in a binary file with no regard for format and figure it out later
}

Core::Core() {

}

void Core::main_loop() {

}

void Core::route_event(CoreEvent input_event) {

    if (input_event.context == 0) this->take_core_event(input_event);

    for (uint8_t i = 0; i < this->event_queues.size(); ++i) {
        if (this->event_queues[i].is_subscribed_to_event(input_event)) {
            this->event_queues[i].enqueue_event(input_event);
            this->updated_queue = i;
            return;
        }
    }

    this->take_core_event(null_event_copy);

}

bool CoreEventQueue::enqueue_event(CoreEvent input_event) {

    for (uint8_t i = 0; i < this->subscribed_events.size(); ++i) {
        this->event_queue.push_front(input_event);
        return true;
    }

    return false;

}

bool CoreEventQueue::hand_off_control_flow() {
    
    for (uint8_t i = 0; i < this->modules.size(); ++i)
        if (this->modules[i]->isSubscribedToEvent(this->event_queue.front())) {
            this->modules[i]->hand_off_control_flow(this->event_queue.front());
            return true;
        }

    return false;

}

void Core::dispatch_work() {

    if (this->event_queues[this->updated_queue].hand_off_control_flow()) this->take_core_event(null_event_copy);

}