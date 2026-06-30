#pragma once

// ==================== Includes ====================
#include <compare>
#include <cstddef>

namespace Core::Type {

    struct Index2D
    {
        size_t row;
        size_t col;

        auto operator<=>(const Index2D&) const = default;

        Index2D& operator+=(const Index2D& other)
        {
            row += other.row;
            col += other.col;
            return *this;
        }

        Index2D& operator-=(const Index2D& other)
        {
            row -= other.row;
            col -= other.col;
            return *this;
        }

    };

    inline Index2D operator+(Index2D lhs, const Index2D& rhs) { return lhs += rhs; }
    inline Index2D operator-(Index2D lhs, const Index2D& rhs) { return lhs -= rhs; }
}