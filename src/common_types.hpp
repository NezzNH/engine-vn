#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <cstdint>

struct Point2D {
    uint16_t x, y;
};

struct RectBounds{
    Point2D left_upper_bound, right_lower_bound;
};

struct RectLengths{
    uint16_t width, height;
};

#endif