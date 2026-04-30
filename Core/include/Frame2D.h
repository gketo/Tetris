#pragma once

#include "Cell.h"
#include "IRenderable.h"
#include "Logger.h"

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace Core::Grid2D {

    template<typename TCell>
    using CellGrid = std::vector<std::vector<Cell<TCell>>>;

    template<typename TCell>
    using CellRow = std::vector<Cell<TCell>>;

    
    template<typename TCell>
    class Frame2D : public IRenderable
    {
    public:
        Frame2D() = default;

        Frame2D(size_t rows, size_t cols, const Cell<TCell>& defaultCell = Cell<TCell>{})
        : m_cols{ cols }
        {
            resize(rows, cols, defaultCell);
        }

        size_t rows() const;
        bool isEmpty() const override;

        const Cell<TCell>& getCell(size_t row, size_t col) const;
        Cell<TCell>& getCell(size_t row, size_t col);
        void setCell(size_t row, size_t col, const Cell<TCell>& cell);
        
        const CellGrid<TCell>& getGrid() const;

        void safeSetCell(Frame2D& frame, size_t row, size_t col, const Cell<TCell>& cell);        

        void resize(size_t nrows, size_t ncols, const Cell<TCell>& defaultCell = Cell<TCell>{});

        void appendRow(CellRow<TCell> row);
        void appendColumn(const Cell<TCell>& defaultCell = Cell<TCell>{});
        
        void clear(const Cell<TCell>& fillCell = Cell<TCell>{});
        void flush();  

    private:
        CellGrid<TCell> m_grid;
        size_t m_cols;
    };

    // get row size
    template<typename TCell>
    size_t Frame2D<TCell>::rows() const
    {
        return m_grid.size();
    }

    template<typename TCell>
    bool Frame2D<TCell>::isEmpty() const
    {
        return m_grid.empty();
    }

    // get a cell (const version)
    template<typename TCell>
    const Cell<TCell>& Frame2D<TCell>::getCell(size_t row, size_t col) const
    {
        if (row >= rows() || col >= m_cols)
        {
            throw std::out_of_range("Frame2D<TCell>::set index out of bounds");
        }
        return m_grid[row][col];
    }

    // get a cell (non-const, for modification)
    template<typename TCell>
    Cell<TCell>& Frame2D<TCell>::getCell(size_t row, size_t col)
    {
        if (row >= rows() || col >= m_cols)
        {
            throw std::out_of_range("Frame2D<TCell>::set index out of bounds");
        }
        return m_grid[row][col];
    }

    // set a specific cell throws
    template<typename TCell>
    void Frame2D<TCell>::setCell(size_t row, size_t col, const Cell<TCell>& cell) 
    {
        if (row >= rows() || col >= m_cols)
        {
            throw std::out_of_range("Frame2D<TCell>::set index out of bounds");
        }
        m_grid[row][col] = cell;
    }

    template<typename TCell>
    const CellGrid<TCell>& Frame2D<TCell>::getGrid() const
    {
        return m_grid;
    }
    
    // set a specific cell without error handling
    template<typename TCell>
    void Frame2D<TCell>::safeSetCell(Frame2D& frame, size_t row, size_t col, const Cell<TCell>& cell) 
    {
        try 
        {
            frame.setCell(row, col, cell);
        } 
        catch (const std::out_of_range& e) 
        {
            LOG_ERROR("[Warning] Could not set cell at (%s, %s): %s", row, col, e.what());
            // optionally clamp coordinates or ignore
        }
    }

    // resize cells vector and initialize
    template<typename TCell>
    void Frame2D<TCell>::resize(size_t nrows, size_t ncols, const Cell<TCell>& defaultCell) 
    {
        m_cols = ncols;

        m_grid.resize(nrows);
        
        for (auto& row : m_grid) 
        {
            row.resize(m_cols, defaultCell);
        }
    }

    // add a row at the end
    template<typename TCell>
    void Frame2D<TCell>::appendRow(CellRow<TCell> row) // pass by value because we don't want to modify caller's row
    {
        size_t newCols = std::max(m_cols, row.size());

        // Ensure all existing rows match the new column count
        resize(m_grid.size(), newCols); // uses default Cell<TCell>{}

        // Pad the new row if needed
        if (row.size() < newCols)
        {
            row.resize(newCols);
        }

        // Add the row
        m_grid.push_back(std::move(row));

        m_cols = newCols;
    }

    // add a column at the end (adds a Cell to each row)
    template<typename TCell>
    void Frame2D<TCell>::appendColumn(const Cell<TCell>& defaultCell)
    {
        size_t ncolIndex = m_cols;
        size_t ncolsSize = m_cols + 1;

        if (!rows()) // if no rows, we keep empty
        {
            throw std::runtime_error("Frame2D<TCell>::appendRow: Grid contains no rows "); // real error
        }

        for (auto& row : m_grid)
        {
            if (row.size() < ncolsSize) // make sure row is long enough
            {
                row.resize(ncolsSize, defaultCell);
            }
            else
            {
                row[ncolIndex] = defaultCell;       // overwrite existing
            }
        }
        ++m_cols;
    }

    // reset all cells to default
    template<typename TCell>
    void Frame2D<TCell>::clear(const Cell<TCell>& fillCell) {
        for (auto& row : m_grid)
        {
            std::fill(row.begin(), row.end(), fillCell);
        }
    }

    // empty cells vector
    template<typename TCell>
    void Frame2D<TCell>::flush()
    {
        m_grid.clear();
    }

}