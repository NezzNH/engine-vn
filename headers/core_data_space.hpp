#ifndef CORE_DATA_SPACE_H
#define CORE_DATA_SPACE_H

#include <cstdint>
#include <vector>
#include <string>

struct CoreDataType {
    std::string data_type_id;
};

struct CoreDataTypeRegister{
    std::string description;
};

/*class CoreDataTypeIndex {
private:
    std::vector<CoreDataType> data_types;
public:
    bool is_valid_data_type(CoreDataType);

    void register_data_type(CoreDataType);
    void convert_from_registry(std::vector<CoreDataTypeRegister>); //TODO probably not necessary
};*/

class CoreDataTypeRegistry {
private:
    std::vector<CoreDataTypeRegister> registers;
public:
    bool is_registered_data_type(CoreDataType);

    std::string get_data_type_details(CoreDataType); //TODO maybe add a fixed width version of this function,
                                                     //so inplace construction of the CoreDataType struct is skipped
};

struct CoreDataSpaceHeader {
    std::string data_header_id;
    CoreDataType data_type;
    uint64_t max_data_size;
};

struct CoreDataSpaceSection {
    CoreDataSpaceHeader header;
    std::vector<uint8_t> byte_data;
};

class CoreDataSpace {
private:
    std::map<std::string, CoreDataSpaceSection> data_sections;
public:
    CoreDataSpace();

    void clear();

    bool contains_data_header(std::string);
    bool register_new_header(std::string, std::string, uint64_t);

    void set_body_data(std::string, std::vector<uint8_t>); //TODO make this a bool, or better yet, make a better exception handling system for intermodular communication
};

#endif
