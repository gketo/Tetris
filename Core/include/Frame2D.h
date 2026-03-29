#pragma once

#include "Cell.h"
#include "IGrid2D.h"
#include "IRenderable.h"

#include <vector>
//todo forward declare cell
namespace Core {

    using CellGrid = std::vector<std::vector<Cell>>;

    class IRenderer;
    
    class Frame2D : public IGrid2D<Cell>, public IRenderable
    {
    public:        
        Frame2D(size_t rows, size_t cols, const Cell& defaultCell = Cell{})
        : IGrid2D {rows, cols}
        {
            resize(rows, cols, defaultCell);
        }

        void accept(IRenderer& renderer) const override;

        const Cell& getCell(size_t row, size_t col) const override;
        Cell& getCell(size_t row, size_t col) override;
        void setCell(size_t row, size_t col, const Cell& cell) override;
        
        const CellGrid getGrid() const;

        void safeSetCell(Frame2D& frame, size_t row, size_t col, const Cell& cell);        

        void resize(size_t nrows, size_t ncols, const Cell& defaultCell = Cell{});

        void appendRow(const std::vector<Cell>& row);
        void appendColumn(const Cell& defaultCell = Cell{});
        
        void clear(const Cell& fillCell = Cell{});
        void flush();
        
    private:
        CellGrid m_grid;
    };

} // namespace Core