#pragma once

#include <cstddef>

namespace App::Grid {

    struct GridSize
    {
        size_t rows;
        size_t cols;

        GridSize& operator+=(const GridSize& other)
        {
            rows += other.rows;
            cols += other.cols;
            return *this;
        }
        GridSize& operator-=(const GridSize& other)
        {
            rows -= other.rows;
            cols -= other.cols;
            return *this;
        }

    };
    
    inline GridSize operator+(GridSize lhs, const GridSize& rhs) { return lhs += rhs; }
    inline GridSize operator-(GridSize lhs, const GridSize& rhs) { return lhs -= rhs; }
}