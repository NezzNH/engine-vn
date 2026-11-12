#include "core_event.hpp"

#include <cstdint>

std::string get_context_of_event(std::string input) {
    uint16_t context_name_length = 0; //TODO if context names ever expand in strlen, change this

    for (uint16_t i = 0; i < input.length() && input[i] != ';'; ++i) 
        context_name_length++;
    
    return std::string{input.substr(0, context_name_length)};
}

std::string get_name_of_event(std::string input) {
    uint16_t context_name_length = 0;

    for (uint16_t i = 0; i < input.length() && input[i] != ';'; ++i) 
        context_name_length++;

    return std::string{input.substr(context_name_length+1, input.length() - context_name_length - 1)};
}