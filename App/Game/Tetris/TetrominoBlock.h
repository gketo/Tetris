#pragma once

#include "Core/Types/Index2D.h"
#include "Core/Containers/Board/CellVisual.h"
#include "Core/Graphics/GfxUtils.h"
#include "Core/Lib/Matrix/Matrix.h"

#include <cstddef>

namespace App::Game::Tetris {

    namespace GfxUtils = Core::Graphics::Utils;

    class TetrominoBlock
    {
    public:
        // TetrominoBlock(size_t row, size_t col)
        // : m_externCoords{ row, col }
        // {}

        TetrominoBlock(int id, const Lib::Matrix::Matrix<int>& shape, const Core::Type::Index2D& topLeft)
        : m_id{ id }
        {
            init(shape, topLeft);
        }

        GfxUtils::Color color() const { return m_blockColor; }

        void setColor(GfxUtils::Color blockColor) { m_blockColor = blockColor; }

        size_t row() const { return m_externCoords.row; }
        size_t col() const { return m_externCoords.col; }

        void translateLeft() { m_externCoords.col--; }
        void translateRight() { m_externCoords.col++; }
        void translateDown(size_t speed) { m_externCoords.row += speed; } 

        const Core::Type::Index2D& updateCoords(const Lib::Matrix::Matrix<int>& oldShape, const Lib::Matrix::Matrix<int>& newShape);

    private:
        int m_id{ -1 };
        Core::Type::Index2D m_externCoords;
        GfxUtils::Color m_blockColor;

        void init(const Lib::Matrix::Matrix<int>& shape, const Core::Type::Index2D& topLeft);
    };
}