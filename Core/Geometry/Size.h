#pragma once

// ==================== Includes ====================
#include <compare>
#include <cstddef>

namespace Core::Geometry {

    struct Size
    {
        size_t width;
        size_t height;

        auto operator<=>(const Size&) const = default;

        Size& operator+=(const Size& other)
        {
            width += other.width;
            height += other.height;
            return *this;
        }
        Size& operator-=(const Size& other)
        {
            width -= other.width;
            height -= other.height;
            return *this;
        }

    };
    
    inline Size operator+(Size lhs, const Size& rhs) { return lhs += rhs; }
    inline Size operator-(Size lhs, const Size& rhs) { return lhs -= rhs; }
}