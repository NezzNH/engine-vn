#include "core_data_space.hpp"

void CoreDataSpace::clear() {
    this->data_sections.clear();
}

bool CoreDataSpace::contains_data_header(CoreDataSpaceHeader data_header) {
    for (uint64_t i = 0; i < this->data_sections.size(); ++i) {
        if (data_sections[i].header.data_header_id == data_header.data_header_id)
            return true;
    }

    return false;
}

uint64_t CoreDataSpace::find_data_section_index(CoreDataSpaceHeader data_header) {
    for (uint64_t i = 0; i < this->data_sections.size(); ++i) {
        if (data_sections[i].header.data_header_id == data_header.data_header_id)
            return i;
    }

    return 0;
} 

void CoreDataSpace::set_body_data(CoreDataSpaceHeader data_header, std::vector<uint8_t> byte_data) {
    if (!(this->contains_data_header(data_header))) return; //TODO add error handling

    this->data_sections[this->find_data_section_index(data_header)].byte_data = std::move(byte_data);
}

void CoreDataSpace::add_data_header(CoreDataSpaceHeader data_header) {
    if (this->contains_data_header(data_header)) return; //TODO add error handling

    CoreDataSpaceSection new_section = {{data_header}, {}};

    this->data_sections.push_back(new_section);
}

void CoreDataSpace::add_body_data(CoreDataSpaceHeader data_header, std::vector<uint8_t> byte_data) {
    if (!(this->contains_data_header(data_header))) return; //TODO add error handling

    uint64_t data_section_index = this->find_data_section_index(data_header);

    this->data_sections[data_section_index].byte_data.insert(this->data_sections[data_section_index].byte_data.end(),
                                                             std::make_move_iterator(byte_data.begin()),
                                                             std::make_move_iterator(byte_data.end()));
}

void CoreDataSpace::add_data_header_and_set_body_data(CoreDataSpaceHeader data_header, std::vector<uint8_t> byte_data) {
    if (this->contains_data_header(data_header)) return; //TODO add error handling

    CoreDataSpaceSection new_section = {{data_header}, {std::move(byte_data)}};

    this->data_sections.push_back(new_section);
}