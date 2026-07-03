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

    if (output_string.empty()) return false;

    unsigned long written; //this is so stupid, find out if you can pass nullptr here without crash
    wchar_t* display_buffer;

    int utf16size = MultiByteToWideChar(CP_UTF8, 0, output_string.data(), output_string.size(), 0, 0);

    display_buffer = new wchar_t[utf16size];

    MultiByteToWideChar(CP_UTF8, 0, output_string.data(), output_string.size(), display_buffer, utf16size);

    #ifdef _WIN32
        bool result = WriteConsoleW(this->stdOHandle, display_buffer, utf16size, &written, NULL);
    #elif __linux__
    #endif

    delete[] display_buffer;

    return result;

}

bool Console::write_at_cursor(wchar_t output_char) {

    unsigned long written;

    #ifdef WIN32
        bool result = WriteConsoleW(this->stdOHandle, &output_char, 1, &written, NULL);
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