#include "core_data_space.hpp"

void CoreDataSpace::clear() {
    this->data_sections.clear();
}

bool CoreDataSpace::contains_data_header(std::string data_section_id) {
    return this->data_sections.contains(data_section_id);
}
