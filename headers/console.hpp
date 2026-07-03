#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <cstdint>
#include <array>
#include <vector>

#include "common_types.hpp"
#include "utf8.h"
#include "utf8/cpp20.h"


#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#endif

class Console {
private:
    Point2D cursor_position;
    RectLengths current_dimensions, maximum_dimensions;

    #ifdef _WIN32

    HANDLE stdIHandle, stdOHandle, stdErrHandle;

    #elif __linux__
    #endif
public:
    Console();

    bool write_at_cursor(std::string);
    bool write_region();
    bool write_at_cursor(wchar_t);

    #ifdef _WIN32
        HANDLE get_Ihandle();
        bool read_inputs(INPUT_RECORD*, uint32_t, unsigned long*);
    #elif __linux__
    #endif
};

#endif