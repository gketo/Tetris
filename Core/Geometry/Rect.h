#pragma once

#include "Point.h"
#include "Size.h"

#include <cstddef>

namespace Core::Geometry {
    
    struct Rect
    {
        Point start;    // start point of the rectangle
        Size size;      // dimension of the rectangle
    };
}