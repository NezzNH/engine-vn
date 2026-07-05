#include "console.hpp"

constexpr uint8_t ANSI_ESCAPE_SEQUENCE_COUNT = 15;

std::array<const char*, ANSI_ESCAPE_SEQUENCE_COUNT> ANSI_ESCAPE_SEQUENCES = {
    "H", //send cursor to home 
    "2J;3J", //clear screen and scrollback buffer
    "0m", //reset all stylings
    "1m", //set bold
    "22m", //reset bold
    "2m", //set dim
    "22m", //reset dim (while they are the same, this was duplicated for symmetry on the caller side in display)
    "3m", //set italic
    "23m", //reset italic
    "4m", //set underline
    "24m", //reset underline
    "5m", //set blinking
    "25m", //reset blinking
    "9m", //set strikethrough
    "29m" //reset strikethrough
};

Console::Console() {

    this->cursor_position.y = this->cursor_position.x = 0;

    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO info;
        AllocConsole(); //TODO introduce error handling

        this->stdOHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        this->stdIHandle = GetStdHandle(STD_INPUT_HANDLE);
        this->stdErrHandle = GetStdHandle(STD_ERROR_HANDLE);

        bool result = GetConsoleScreenBufferInfo(this->stdOHandle, &info);

        current_dimensions.height = info.dwSize.X;
        current_dimensions.width = info.dwSize.Y;
        maximum_dimensions.height = info.dwMaximumWindowSize.X;
        maximum_dimensions.width = info.dwMaximumWindowSize.Y;

        DWORD mode;
        GetConsoleMode(stdIHandle, &mode);

        mode &= ~(ENABLE_MOUSE_INPUT);
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; //for ANSI escape sequences (styling output and cursor pos)
        SetConsoleMode(stdIHandle, mode);

    #elif __linux__
    #endif
}

void Console::write_attribute(uint8_t attribute_index) {
    if (attribute_index < 0 || attribute_index > ANSI_ESCAPE_SEQUENCE_COUNT) return;

    std::string output = "\033[" + std::string(ANSI_ESCAPE_SEQUENCES[attribute_index]);

    unsigned long blerb;

    #ifdef _WIN32
        WriteConsoleA(this->stdOHandle, output.data(), output.length(), &blerb, NULL);
    #elif __linux__
    #endif
}

bool Console::write_at_cursor(std::string output_string) {
    unsigned long written;

    if (output_string.empty()) return false;

    #ifdef _WIN32
        bool result = WriteConsoleA(this->stdOHandle, output_string.data(), output_string.size(), &written, NULL);
    #elif __linux__
    #endif

    return result;
}

#ifdef _WIN32
    inline HANDLE Console::get_Ihandle() {return this->stdOHandle;}

    bool Console::read_inputs(INPUT_RECORD* records_array, uint32_t records_size, unsigned long* read_counter) {
        return ReadConsoleInput(this->stdIHandle, records_array, records_size, read_counter);
    }
#elif __linux__
#endif