#pragma once

// ==================== Includes ====================
#include "Core/Containers/Board/Cell.h"

#include "Core/Lib/Matrix/Matrix.h"
#include "Core/Lib/Matrix/MatrixStridedSpan.h"

#include "Core/Render/IRenderable.h"

#include "Core/Types/Size2D.h"

// ==================== Includes ====================
#include <concepts>
#include <cstddef>

namespace Core::Container {

    class Board : public Core::IRenderable
    {
    public:
        Board(size_t rows, size_t cols)
        : m_matrix{ rows, cols }
        {}

        Board(size_t rows, size_t cols, const Cell& defaultCell)
            : m_matrix{ rows, cols, Cell(defaultCell) }
        {}

        Lib::Matrix::Matrix<Cell> data() const { return m_matrix; }
        bool empty() const { return m_matrix.empty(); }
        Core::Type::Size2D size() const { return { m_matrix.rows(), m_matrix.cols() }; }
        size_t rows() const { return m_matrix.rows(); }
        size_t cols() const { return m_matrix.cols(); }
        Lib::Matrix::MatrixStridedSpan<const Cell> row(size_t r) const { return m_matrix.row(r); }
        Lib::Matrix::MatrixStridedSpan<const Cell> col(size_t c) const { return m_matrix.col(c); }
    
        void reset(const Cell& fillCell) { m_matrix.reset(fillCell); }
        void set(size_t r, size_t c, const Cell& content) { m_matrix.set(r, c, content); }
        const Cell& at(size_t r, size_t c) const { return m_matrix.at(r, c); }
        Cell& at(size_t r, size_t c) { return m_matrix.at(r, c); }

    protected:
        Lib::Matrix::Matrix<Cell> m_matrix;
    };
}