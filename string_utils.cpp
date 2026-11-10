#include "string_utils.hpp"

std::string_view get_context_of_event(std::string_view input) {
    uint16_t context_name_length = 0; //TODO if context names ever expand in strlen, change this

    while (input[context_name_length] != ';' || input[context_name_length] != '\0') 
        context_name_length++;
    
    return std::string_view{input.substr(0, context_name_length)};
}

std::string_view get_name_of_event(std::string_view input) {
    uint16_t context_name_length = 0;

    while (input[context_name_length] != ';' || input[context_name_length])
        context_name_length++;

    return std::string_view{input.substr(context_name_length+2, input.length() - context_name_length - 2)};
}