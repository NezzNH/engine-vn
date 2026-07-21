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

void Display::write_string_to_screen(std::string display_string) {
    this->console.write_at_cursor(display_string);
} //TODO remove this function, its just for debugging for now!

CoreEvent Display::hand_off_control_flow(CoreEvent input_event) {
    switch (input_event.event_id) {
        
    }
}

void Display::hand_off_event(CoreEvent input_event) {

}

Display::Display() {
    this->event_registry = CoreEventRegistry(1);
    this->event_registry.register_new_event(0, 1, "Clear display", "Clears the display");
    this->event_registry.register_new_event(1, 1, "Update output", "Updates the output buffer and draws");
    this->event_registry.register_new_event(2, 1, "Window Resize", "Window resize happened");
}

CoreEventRegistry Display::get_event_registry() {return this->event_registry;} // TODO make inline