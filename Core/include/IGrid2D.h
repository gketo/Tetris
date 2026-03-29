#pragma once

#include <cstddef>

namespace Core
{
    template <typename CellType>
    class IGrid2D 
    {
    public:
        IGrid2D(size_t rows, size_t cols)
        : rows{ rows }
        , cols{ cols }
        {}

        virtual ~IGrid2D() = default;

        virtual CellType& getCell(size_t row, size_t col) = 0;
        virtual const CellType& getCell(size_t row, size_t col) const = 0;
        virtual void setCell(size_t row, size_t col, const CellType& cell) = 0;

    protected:
        size_t rows;
        size_t cols;
    };
    
} // namespace Core

