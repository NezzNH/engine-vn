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

CoreDataSpaceHeader CoreDataSpace::register_new_header(CoreDataType data_type) {

    //NOTE : for now, IDs will be sequential. the reason why code above checks
    //through all data headers to find the right one instead of just using the id's as an index
    //is because in the future i plan to make register_new_header and IDs in general random

    //the reason ive not done it now is because mt19937 is best used when compiling with -O2 and above
    //which i dont plan to use right now. its possible i could use a simpler PRNG but right now ill just
    //make it sequential for simplicity of debugging

    CoreDataSpaceHeader new_header = this->data_sections.back().header;
    new_header.data_header_id++;
    new_header.data_type = data_type;

    CoreDataSpaceSection new_section = {{new_header}, {}};
    this->data_sections.push_back(new_section);

    return new_header;
}