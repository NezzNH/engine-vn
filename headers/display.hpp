#ifndef DISPLAY_H
#define DISPLAY_H

#include <bitset>
#include <cstdint>

#include "console.hpp"

namespace DisplayConstants {
    constexpr uint8_t BOLD_INDEX = 0;
    constexpr uint8_t DIM_INDEX = 1;
    constexpr uint8_t ITALIC_INDEX = 2;
    constexpr uint8_t UNDERLINE_INDEX = 3;
    constexpr uint8_t BLINKING_INDEX = 4;
    constexpr uint8_t STRIKETHROUGH_INDEX = 5;
};

struct DisplayCharacter{
    char display_symbol;
    std::bitset<ANSI_ESCAPE_ATTRIBUTE_COUNT> attributes;
};

class Display{
private:
    Console console;
    std::bitset<ANSI_ESCAPE_ATTRIBUTE_COUNT> current_display_attributes;
public:
    Display();

    void reset_screen();

    void write_to_screen(std::vector<DisplayCharacter>);
};

#endif