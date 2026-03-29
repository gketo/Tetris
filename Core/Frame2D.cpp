#include "Frame2D.h"

#include "Cell.h"
#include "Logger.h"
#include "IRenderer.h"

namespace Core {

    // visitor pattern
    void Frame2D::accept(IRenderer& renderer) const
    {
        renderer.render(*this);
    }

    // get a cell (const version)
    const Cell& Frame2D::getCell(size_t row, size_t col) const
    {
        return m_grid[row][col];
    }

    // get a cell (non-const, for modification)
    Cell& Frame2D::getCell(size_t row, size_t col)
    {
        return m_grid[row][col];
    }

    // set a specific cell throws
    void Frame2D::setCell(size_t row, size_t col, const Cell& cell) 
    {
        if (row >= rows || col >= cols)
        {
            throw std::out_of_range("Frame2D::set index out of bounds");
        }
        m_grid[row][col] = cell;
    }

    const CellGrid Frame2D::getGrid() const
    {
        return m_grid;
    }
    
    // set a specific cell without error handling
    void Frame2D::safeSetCell(Frame2D& frame, size_t row, size_t col, const Cell& cell) 
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
    void Frame2D::resize(size_t nrows, size_t ncols, const Cell& defaultCell) 
    {
        rows = nrows;
        cols = ncols;

        m_grid.resize(rows);
        for (auto& row : m_grid) 
        {
            row.resize(cols, defaultCell);
        }
    }

    // add a row at the end
    void Frame2D::appendRow(const std::vector<Cell>& row) 
    {
        if (rows >= m_grid.size()) 
        {
            m_grid.push_back(row);
        } 
        else
        {
            m_grid[rows] = row;
        }
        ++rows;
        cols = std::max(cols, row.size());
    }

    // add a column at the end (adds a Cell to each row)
    void Frame2D::appendColumn(const Cell& defaultCell)
    {
        for (auto& row : m_grid)
        {
            if (row.size() < cols + 1) // make sure row is long enough
                row.resize(cols + 1, defaultCell);
            else
                row[cols] = defaultCell;       // overwrite existing
        }
        ++cols;
    }

    // reset all cells to default
    void Frame2D::clear(const Cell& fillCell) {
        for (auto& row : m_grid)
        {
            std::fill(row.begin(), row.end(), fillCell);
        }
    }

    // empty cells vector
    void Frame2D::flush()
    {
        m_grid.clear();
    }

}
