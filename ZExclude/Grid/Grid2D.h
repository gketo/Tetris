#pragma once

#include "Core/GridSize.h"
#include "Core/Render/IRenderable.h"
#include "Core/Utils/Logger.h"
#include "Core/Lib/Matrix/Matrix.h"
#include "Core/Lib/Matrix/MatrixStridedSpan.h"
#include "Core/Tile.h"

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace App::Grid {

    template <typename TTileContent>
    class Grid2D : public Core::IRenderable
    {
    public:
        Grid2D() = default;

        Grid2D(size_t rows, size_t cols)
        : m_matrix{ rows, cols, Tile<TTileContent>() }
        {}

        Grid2D(size_t rows, size_t cols, TTileContent defaultContent)
        : m_matrix{ rows, cols, Tile<TTileContent>(defaultContent) }
        {}

        bool empty() const override 
        { 
            return m_matrix.empty();
        };

        GridSize size() const
        {
            return { m_matrix.rows(), m_matrix.cols() };
        }

        size_t rows() const
        {
            return m_matrix.rows();
        }
        size_t cols() const
        {
            return m_matrix.cols();
        }

        Lib::Matrix::MatrixStridedSpan<const Tile<TTileContent>> row(size_t r) const
        {
            return m_matrix.row(r);
        }
        Lib::Matrix::MatrixStridedSpan<const Tile<TTileContent>> col(size_t c) const
        {
            return m_matrix.col(c);
        }

        void set(size_t r, size_t c, const Tile<TTileContent>& content)
        {
            m_matrix.set(r, c, content);
        }

        const Tile<TTileContent>& at(size_t r, size_t c) const
        {
            return m_matrix.at(r, c);
        }
        
        Tile<TTileContent>& at(size_t r, size_t c)
        {
            return m_matrix.at(r, c);
        }

        void appendRow(const std::vector<Tile<TTileContent>>& row)
        {
            m_matrix.appendRow(row);
        }
        
        void appendCol(const std::vector<TTileContent>& col)
        {
            std::vector<Tile<TTileContent>> buffer;
            buffer.reserve(col.size());

            for (const auto& cell : col)
            {
                buffer.emplace_back(cell); // construct Tile<TTileContent> from TTileContent
            }

            m_matrix.appendCol(buffer);
        }

    private:
        Lib::Matrix::Matrix<Tile<TTileContent>> m_matrix;
    };

}