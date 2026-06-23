#pragma once

#include <cstddef>

namespace App::Grid {

    struct GridCoord
    {
        size_t row;
        size_t col;

        GridCoord& operator+=(const GridCoord& other)
        {
            row += other.row;
            col += other.col;
            return *this;
        }
        GridCoord& operator-=(const GridCoord& other)
        {
            row -= other.row;
            col -= other.col;
            return *this;
        }
        
    };

    inline GridCoord operator+(GridCoord lhs, const GridCoord& rhs) { return lhs += rhs; }
    inline GridCoord operator-(GridCoord lhs, const GridCoord& rhs) { return lhs -= rhs; }
}