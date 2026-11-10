#include "core_module.hpp"

#include <array>
#include <iostream> // TODO remove when done testig plz

static constexpr std::string_view DEFAULT_MODULE_ID{"default"};

static constexpr std::array INCOMING_EVENTS_DECL{
    std::string_view{"core;enable"},
    std::string_view{"core;disable"},
    std::string_view{"core;die"}
};

static constexpr std::array OUTGOING_EVENTS_DECL{
    std::string_view{"core;died"},
    std::string_view{"core;born"}
};

CoreModule::CoreModule() {

    for (int i = 0; i < INCOMING_EVENTS_DECL.size(); ++i) {
        
    }

    this->b_is_busy = false;
    this->data_space_p = nullptr; //TODO these are likely
                                  //default behavior, theres no
                                  //no need to do this

    this->module_id = DEFAULT_MODULE_ID;
}

CoreModule::CoreModule(std::string module_id) : CoreModule() {
    this->module_id = module_id;
}

CoreModule::CoreModule(std::string module_id, CoreDataSpace* data_space_p) : CoreModule() {
    this->module_id = module_id;
    this->data_space_p = data_space_p;
}

