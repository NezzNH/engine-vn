#ifndef DISPLAY_H
#define DISPLAY_H

#include <bitset>
#include <cstdint>

#include "console.hpp"

namespace DisplayConstants {
    constexpr uint8_t CURSOR_HOME_INDEX = 0;
    constexpr uint8_t CLEAR_SCREEN_INDEX = 1;
    constexpr uint8_t RESET_ATTRIBUTES_INDEX = 2;
    constexpr uint8_t SET_BOLD_INDEX = 3;
    constexpr uint8_t RESET_BOLD_INDEX = 4;
    constexpr uint8_t SET_DIM_INDEX = 5;
    constexpr uint8_t RESET_DIM_INDEX = 6;
    constexpr uint8_t SET_ITALIC_INDEX = 7;
    constexpr uint8_t RESET_ITALIC_INDEX = 8;
    constexpr uint8_t SET_UNDERLINE_INDEX = 9;
    constexpr uint8_t RESET_UNDERLINE_INDEX = 10;
    constexpr uint8_t SET_BLINKING_INDEX = 11;
    constexpr uint8_t RESET_BLINKING_INDEX = 12;
    constexpr uint8_t SET_STRIKETHROUGH_INDEX = 13;
    constexpr uint8_t RESET_STRIKETHROUGH_INDEX = 14;
};

struct DisplayCharacter{
    char display_symbol;
    std::bitset<ANSI_ESCAPE_ATTRIBUTE_COUNT> attributes;
};

class Display : public CoreModule {
private:
    Console console;
    std::bitset<ANSI_ESCAPE_ATTRIBUTE_COUNT> current_display_attributes;
public:
    Display();

    CoreEvent hand_off_control_flow(CoreEvent) override;

    void hand_off_event(CoreEvent) override;

    void reset_screen();

    void write_to_screen(std::vector<DisplayCharacter>);
    void write_string_to_screen(std::string);
};

#endif