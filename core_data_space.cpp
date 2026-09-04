#include "core_data_space.hpp"

void CoreDataSpace::clear() {
    this->data_sections.clear();
}

void CoreDataSpace::clear() {
    this->data_sections.clear();
    this->data_byte_positions.clear();
}

bool CoreDataSpace::contains_data_header(std::string data_section_id) {
    return this->data_sections.contains(data_section_id);
}

bool CoreDataSpace::register_new_header(std::string data_section_id, std::string data_type, uint64_t max_data_size) {
    //TODO add available memory checks, see if theres enough space to reserve space for! most likely, this will never NOT be the case, but we must be sure!
    
    if (this->contains_data_header(data_section_id)){
        this->data_sections.at(data_section_id).byte_data.clear();
        return true; //i dont like the nature of this behavior, maybe revisit this
    
    }
    else {
        CoreDataSpaceSection new_section; //TODO make this inline in .emplace() call later on
        new_section.header = {{data_section_id}, {{data_type}}, {max_data_size}};
        this->data_sections.emplace(new_section.data_section_id, new_section);
        return true;
    } //optionally, reserve the appropriate amount of space according to type of data and max specified size. avoids vector resizing operations later on
}

void CoreDataSpace::set_body_data(std::string data_section_id, std::vector<uint8_t> byte_data) {
    if (!(this->contains_data_header(data_section_id)) return;

    this->data_sections.at(data_section_id).byte_data = std::move(byte_data);
}
