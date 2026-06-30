#pragma once

// ==================== Includes ====================
#include "Point.h"
#include "Size.h"

// ==================== Includes ====================
#include <cstddef>

namespace Core::Geometry {
    
    struct Rect
    {
        Point start;    // start point of the rectangle
        Size size;      // dimension of the rectangle
    };
}