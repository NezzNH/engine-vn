#ifndef CORE_DATA_SPACE_H
#define CORE_DATA_SPACE_H

#include <cstdint>
#include <vector>
#include <string>

struct CoreDataType {
    uint8_t data_type_id;
};

struct CoreDataTypeRegister{
    uint8_t data_type_id;
    std::string name, description;
};

class CoreDataTypeIndex {
private:
    std::vector<CoreDataType> data_types;
public:
    bool is_valid_data_type(CoreDataType);

    void register_data_type(CoreDataType);
};

struct CoreDataSpaceHeader {
    uint64_t data_start_index, data_size;
    uint16_t data_header_id;
    CoreDataType data_type;
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
    CoreDataSpaceHeader register_new_header(CoreDataType);

    void add_body_data(CoreDataSpaceHeader, std::vector<uint8_t>);
    void set_body_data(CoreDataSpaceHeader, std::vector<uint8_t>);
    void add_data_header(CoreDataSpaceHeader);
    void add_data_header_and_set_body_data(CoreDataSpaceHeader, std::vector<uint8_t>);
};

#endif