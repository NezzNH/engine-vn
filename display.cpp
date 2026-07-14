#include "display.hpp"

void Display::reset_screen() {
    this->console.write_attribute(DisplayConstants::CURSOR_HOME_INDEX);
    this->console.write_attribute(DisplayConstants::CLEAR_SCREEN_INDEX);

    this->current_display_attributes.reset();
    this->console.write_attribute(DisplayConstants::RESET_ATTRIBUTES_INDEX);
}

void Display::write_to_screen(std::vector<DisplayCharacter> characters) {

    std::string output_buffer;
    std::bitset<ANSI_ESCAPE_ATTRIBUTE_COUNT> attribute_difference;
    attribute_difference.reset();

    for (size_t i = 0; i < characters.size(); ++i) {
        attribute_difference = ~(characters[i].attributes & this->current_display_attributes);

        if (attribute_difference.any()) {
            this->console.write_at_cursor(output_buffer);
            output_buffer.clear();

            for (size_t curr_bit = 0; curr_bit < ANSI_ESCAPE_ATTRIBUTE_COUNT; ++curr_bit) {
                if (attribute_difference[curr_bit]) {
                    if (!(this->current_display_attributes[curr_bit]))
                        this->console.write_attribute(3 + curr_bit*2);
                    else
                        this->console.write_attribute(4 + curr_bit*2);
                }      
            }
        }
        output_buffer += characters[i].display_symbol;
    }

    if (!(output_buffer.empty())) this->console.write_at_cursor(output_buffer);

}