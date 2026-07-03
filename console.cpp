#include "console.hpp"

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
        SetConsoleMode(stdIHandle, mode);

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