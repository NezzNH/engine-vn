#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#ifdef _WIN32
    #include <Windows.h>
#elif __linux__
    #include <ncurses>
#endif

#include <string>
#include <vector>
#include <deque>
#include <map>
#include <cstdint>
#include <memory>

#include <iostream>

#include "common_types.hpp"
#include "core_module.hpp"
#include "core.hpp"
#include "console.hpp"
#include "utf8.h"
#include "utf8/cpp20.h"

enum class InputEventType : uint8_t {
    KEYBOARD,
    WINDOW,
    MOUSE,
    OTHER,
    NO_INPUT
};

struct InputEvent{
    InputEventType type;
};

struct KeyboardEvent : public InputEvent {
    public:
        uint32_t key_code, scan_code;
        std::string character_symbol;
        bool key_down;
};

struct WindowResizeEvent : public InputEvent {
    public:
        RectLengths new_size;
};

struct InputHandlerEvent : CoreEvent {
    InputEvent input_data;
};

class InputHandler : public CoreModule {
private:

    std::deque<std::unique_ptr<InputEvent>> input_events;

    Console* console_pointer;

    #ifdef _WIN32
        uint32_t input_record_count;

        void push_input_events();
    #elif __linux__
    #endif

#ifdef _WIN32
    bool get_console_input();
    INPUT_RECORD input_record_array[50];
#elif __linux__
    void push_input_event(idk);
#endif

public:
    InputHandler();
    InputHandler(Console*);

    CoreEvent hand_off_control_flow(CoreEvent) override;
    void hand_off_event(CoreEvent) override;

    InputEventType peek_input_type();

    bool pop_input_event(std::unique_ptr<InputEvent>*);
};

#endif
