#include "core.hpp"

void Core::register_module(std::string module_id,
                     std::vector<std::string> subscribed_events) {
    if (this->core_module_registry.contains_module_register(module_id)) return;

    this->core_module_registry.register_module(module_id, subscribed_events);

}
