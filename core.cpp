#include "core.hpp"

CoreEventRegistry::CoreEventRegistry() {
    this->contexts.push_back({
        {
            {
                {
                    "force_shutdown"
                },
                {
                    "Quits the entire program immediately without any exit procedure. Loses all data."
                },
                {
                    {0}, {0}
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
                    {1}, {0}
                }
            }
        },
        "CoreEvents",
        "Events used to signal broad program changes to the core or system specific requests",
        0
    });
} //TODO this goes without saying, but all of this should be moved externally to a file.
  //if it quacks like a JSON and walks like a JSON...
  //shove it in a binary file with no regard for format and figure it out later

Core::Core() {

}