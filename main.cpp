#include "main.hpp"

int main() {

    Console main_console;
    InputHandler input(&main_console);

    std::string output_buffer;
    std::unique_ptr<InputEvent> event;
    KeyboardEvent* key_event;
    WindowResizeEvent* window_event;

    bool ignore_other_events = true;

    while (1) {
        output_buffer = "";
        switch (input.peek_input_type()) {
            case InputEventType::KEYBOARD:
                input.pop_input_event(&event);
                key_event = static_cast<KeyboardEvent*>(event.get());
                if (key_event->key_down) output_buffer = key_event->character_symbol;
                break;
            case InputEventType::WINDOW:
                input.pop_input_event(&event);
                window_event = static_cast<WindowResizeEvent*>(event.get());
                std::cout << window_event->new_size.height << ";" << window_event->new_size.width;
                break;
            case InputEventType::OTHER:
                input.pop_input_event(nullptr);
                output_buffer = "other\n";
                break;
            case InputEventType::NO_INPUT:
                if (!ignore_other_events) output_buffer = "no_input";
                break;
            default:
                output_buffer = "unsupported_event";
                break;
        }        
        main_console.write_at_cursor(output_buffer);
    }

    return 0;

}