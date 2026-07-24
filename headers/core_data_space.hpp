#ifndef CORE_DATA_SPACE_H
#define CORE_DATA_SPACE_H

#include <cstdint>
#include <vector>

struct CoreDataSpaceHeader {
    uint64_t data_start_index, data_size;
    uint16_t data_header_id;
    uint8_t data_type_id;
};

struct CoreDataSpaceSection {
    CoreDataSpaceHeader header;
    std::vector<uint8_t> byte_data;
};

class CoreDataSpace {
private:
    std::vector<CoreDataSpaceSection> data_sections;
    
    uint64_t find_data_section_index(CoreDataSpaceHeader);
public:
    CoreDataSpace();

    void clear();

    bool contains_data_header(CoreDataSpaceHeader);

    void add_body_data(CoreDataSpaceHeader, std::vector<uint8_t>);
    void set_body_data(CoreDataSpaceHeader, std::vector<uint8_t>);
    void add_data_header(CoreDataSpaceHeader);
    void add_data_header_and_set_body_data(CoreDataSpaceHeader, std::vector<uint8_t>);
};

#endif