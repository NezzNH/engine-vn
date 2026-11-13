#include "core_module.hpp"

#include <array>
#include <iostream> // TODO remove when done testig plz

static constexpr std::string_view DEFAULT_MODULE_ID{"default"};

std::array INCOMING_EVENTS_DECL{
    std::string{"core;enable"},
    std::string{"core;disable"},
    std::string{"core;die"}
};

std::array OUTGOING_EVENTS_DECL{
    std::string{"core;died"},
    std::string{"core;born"},
    std::string{"core;blank"}
};

void CoreModule::add_incoming_event_subscription(std::string event) {

    bool context_collision = false;
    uint16_t context_collision_index;

    for (uint16_t i = 0; i < this->incoming_events.size(); ++i) {
        if (this->incoming_events.at(i).context_id == get_context_of_event(event)) {
            context_collision = true;
            context_collision_index = i;
            break;
        }
    }

    if (context_collision)
        this->incoming_events.
            at(context_collision_index).
            event_ids.push_back(
                get_name_of_event(event)
        );
    else {
        this->incoming_events.push_back(CoreEventContextIndex());

        this->incoming_events.back().context_id = get_context_of_event(event);

        this->incoming_events.back().
        event_ids.push_back(
            get_name_of_event(event)
        );
    }
}

void CoreModule::add_outgoing_event_subscription(std::string event) {

    bool context_collision = false;
    uint16_t context_collision_index;

    for (uint16_t i = 0; i < this->outgoing_events.size(); ++i) {
        if (this->outgoing_events.at(i).context_id == get_context_of_event(event)) {
            context_collision = true;
            context_collision_index = i;
            break;
        }
    }

    if (context_collision)
        this->outgoing_events.
            at(context_collision_index).
            event_ids.push_back(
                get_name_of_event(event)
        );
    else {
        this->outgoing_events.push_back(CoreEventContextIndex());

        this->outgoing_events.back().context_id = get_context_of_event(event);

        this->outgoing_events.back().
        event_ids.push_back(
            get_name_of_event(event)
        );
    }
}

CoreModule::CoreModule() {
    for (uint16_t i = 0; i < INCOMING_EVENTS_DECL.size(); ++i)
        this->add_incoming_event_subscription(INCOMING_EVENTS_DECL[i]);
    
    for (uint16_t i = 0; i < OUTGOING_EVENTS_DECL.size(); ++i)
        this->add_outgoing_event_subscription(OUTGOING_EVENTS_DECL[i]);

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

std::vector<std::string> CoreModule::get_incoming_events() {
    std::string curr_context;
    std::vector<std::string> result;

    for (uint16_t i = 0; i < this->incoming_events.size(); ++i) {
        curr_context = this->incoming_events.at(i).context_id;
        for (uint16_t j = 0; j < this->incoming_events.at(i).event_ids.size(); ++j) {
            result.push_back(curr_context + ";" + this->incoming_events.at(i).event_ids.at(j));
        }
    }

    return result;
}

std::vector<std::string> CoreModule::get_outgoing_events() {
    std::string curr_context;
    std::vector<std::string> result;

    for (uint16_t i = 0; i < this->outgoing_events.size(); ++i) {
        curr_context = this->outgoing_events.at(i).context_id;
        for (uint16_t j = 0; j < this->outgoing_events.at(i).event_ids.size(); ++j) {
            result.push_back(curr_context + ";" + this->outgoing_events.at(i).event_ids.at(j));
        }
    }

    return result;
}

bool CoreModule::is_active() {return this->b_is_active;}
void CoreModule::activate_module() {this->b_is_active = true;}
void CoreModule::deactivate_module() {this->b_is_active = false;}

bool CoreModule::is_subscribed_to_event(std::string event) {
    return this->is_subscribed_to_event(CoreEvent{
        get_context_of_event(event),
        get_name_of_event(event)});
}

bool CoreModule::is_subscribed_to_event(CoreEvent event){
    bool context_collision = false;
    uint16_t context_collision_index;

    for (uint16_t i = 0; i < this->incoming_events.size(); ++i) {
        if (event.context_id == this->incoming_events.at(i).context_id) {
            context_collision = true;
            context_collision_index = i;
            break;
        }
    }

    if (!context_collision)
        return false;
    else {
        for (uint16_t i = 0; 
            i < this->incoming_events.
            at(context_collision_index).event_ids.size(); ++i)
        if (event.event_id == this->incoming_events.at(context_collision_index).event_ids.at(i))
            return true;
    }
    return false;
}

bool CoreModule::is_subscribed_to_event(CoreDataEvent event) {
    //return this->is_subscribed_to_event(event) CHECK IF THIS DOWNCASTING LOSES VITAL DATA. IF NOT WE CAN DO THIS :O

    return this->is_subscribed_to_event(CoreEvent{event.context_id,event.event_id});
}

uint64_t CoreModule::get_instance_id() {return this->instance_id;}

void CoreModule::set_instance_id(uint64_t instance_id) {
    this->instance_id = instance_id;}


