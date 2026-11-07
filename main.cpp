#include "main.hpp"

int main() {

    /*
        MVP is:
        1. Invoke three modules:
            One sends an update signal
            One increments an integer
            One displays the integer's value when updated
        2. Send 20 events, incrementing the number from 0 to n
        3. Graciously exit the program

        Detailed steps required for each MVP clause:
        For invoking the three modules:
            Set up a core module registry in the core.
            The core module registry must contain:
                The list of all module_type_IDs that the core knows what to do with
                Each module_type_ID has a set of incoming and outgoing events
            
            Set up a core state that runs the program.
            The core state must contain:
                An appropriate amount of queues for the modules
                Valid queue subscriptions so module events are passed accordingly
        
        For sending the events:
            Appropriate synchronous control flow:
                1. Upon finishing set-up (applying a core state), the initial module is called (or an initializing event is sent).
                2. The control flow is handed off to the module, by calling it from the running Core loop function
                3. The module completes work, and returns a CoreEvent
                4. The core loop function gets the CoreEvent, calls RouteEvent and the Event is sent to the appropriate Queue
                5. The Queue checks for valid modules, then step 2 repeats, until a terminate program event is sent
                    OR
                   A change state event is sent
        
        For graciously exiting the program:
            Clean up all objects, (serialize if possible any information in the data_spaces), and close.
    */

    IntegerIterator it1;

}