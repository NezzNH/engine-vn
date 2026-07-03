#include "input_handler.hpp"

#ifdef _WIN32
void InputHandler::push_input_events() {
    KeyboardEvent key_event;
    WindowResizeEvent window_resize_event;
    InputEvent generic_event;

    std::unique_ptr<KeyboardEvent> q_front;

    for (int i = 0; i < this->input_record_count; ++i) {
        switch (this->input_record_array[i].EventType) {
            case KEY_EVENT:
                q_front = std::make_unique<KeyboardEvent>();

                q_front->type = InputEventType::KEYBOARD;
                q_front->key_code = this->input_record_array[i].Event.KeyEvent.wVirtualKeyCode;
                q_front->scan_code = this->input_record_array[i].Event.KeyEvent.wVirtualScanCode;
                q_front->character_symbol = this->input_record_array[i].Event.KeyEvent.uChar.AsciiChar;
                q_front->key_down = this->input_record_array[i].Event.KeyEvent.bKeyDown;

                this->input_events.push_front(std::move(q_front));
            break;
            case WINDOW_BUFFER_SIZE_EVENT:
                window_resize_event.type = InputEventType::WINDOW;

                window_resize_event.new_size.height = static_cast<uint16_t>
                (this->input_record_array[i].Event.WindowBufferSizeEvent.dwSize.X);
                window_resize_event.new_size.width = static_cast<uint16_t>
                (this->input_record_array[i].Event.WindowBufferSizeEvent.dwSize.Y);

                this->input_events.push_front(std::make_unique<WindowResizeEvent>(window_resize_event));
            break;
            default:
                generic_event.type = InputEventType::OTHER;
                this->input_events.push_front(std::make_unique<InputEvent>(generic_event));
            break;
        }
    }
}

InputHandler::InputHandler(Console* console_pointer) {
    this->console_pointer = console_pointer;
}

InputHandler::InputHandler() {
    this->console_pointer = nullptr;
    this->input_record_count = 0;
}

#elif __linux__
#endif

InputEventType InputHandler::peek_input_type() {

    if (this->input_events.empty()) {
        if (!(this->get_console_input())) return InputEventType::NO_INPUT;
    }

    return input_events.front()->type;
}

bool InputHandler::get_console_input() {
    unsigned long events_count;
    
    if (!this->console_pointer->read_inputs(this->input_record_array, 100, &events_count)) return false;
    else {
        this->input_record_count = events_count;
        this->push_input_events();
        return true;
    }
}

bool InputHandler::pop_input_event(std::unique_ptr<InputEvent>* event) {
    if (this->input_events.empty()) {
        if (!(this->get_console_input())) return false;
    }

    if (event != nullptr) *event = std::move(this->input_events.front());
    this->input_events.pop_front();

    return true;
}