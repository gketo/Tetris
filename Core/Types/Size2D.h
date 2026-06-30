#pragma once

// ==================== Includes ====================
#include <compare>
#include <cstddef>

namespace Core::Type {

    struct Size2D
    {
        size_t rows;
        size_t cols;

        auto operator<=>(const Size2D&) const = default;

        Size2D& operator+=(const Size2D& other)
        {
            rows += other.rows;
            cols += other.cols;
            return *this;
        }
        Size2D& operator-=(const Size2D& other)
        {
            rows -= other.rows;
            cols -= other.cols;
            return *this;
        }
        friend Size2D operator+(Size2D lhs, const Size2D& rhs) { return lhs += rhs; }
        friend Size2D operator-(Size2D lhs, const Size2D& rhs) { return lhs -= rhs; }
    };
}