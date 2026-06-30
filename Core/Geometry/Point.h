#pragma once

// ==================== Includes ====================
#include <cstddef>

namespace Core::Geometry {
    
    struct Point
    {
        size_t x;
        size_t y;

        Point& operator+=(const Point& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Point& operator-=(const Point& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }    
    };

    inline Point operator+(Point lhs, const Point& rhs) { return lhs += rhs; }
    inline Point operator-(Point lhs, const Point& rhs) { return lhs -= rhs; }
}