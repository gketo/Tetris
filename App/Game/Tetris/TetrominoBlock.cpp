#include "App/Game/Tetris/TetrominoBlock.h"

#include "Core/Types/Index2D.h"
#include "Core/Graphics/GfxUtils.h"
#include "Core/Lib/Matrix/Matrix.h"

#include <cstddef>
#include <stdexcept>
#include <vector>


namespace App::Game::Tetris {

    namespace GfxUtils = Core::Graphics::Utils;

    void TetrominoBlock::init(const Lib::Matrix::Matrix<int>& shape, const Core::Type::Index2D& topLeft)
    {
        const auto& matches = shape.find(m_id);
        if (matches.empty() || matches.size() > 1)
        {
            throw std::runtime_error("[TetrominoBlock] init(): id error, couldn't find or found more than one match in matrix");
        }
        m_externCoords = { topLeft.row + matches[0].row, topLeft.col + matches[0].col };
    }

    const Core::Type::Index2D& TetrominoBlock::updateCoords(const Lib::Matrix::Matrix<int>& oldShape, const Lib::Matrix::Matrix<int>& newShape)
    {
        if (oldShape.size() != newShape.size())
        {
            throw std::runtime_error("[TetrominoBlock] updateCoords(): Shapes are not the same dimensions");
        }

        if (oldShape == newShape)
        {
            return m_externCoords;
        }

        const auto& matchesOld = oldShape.find(m_id);
        const auto& matchesNew = newShape.find(m_id);
        if (matchesOld.empty() || matchesOld.size() > 1 || matchesNew.empty() || matchesNew.size() > 1)
        {
            throw std::runtime_error("[TetrominoBlock] init(): id error, couldn't find or found more than one match in matrix");
        }

        const auto coordsTranslation = matchesNew.front() - matchesOld.front();
        m_externCoords.row += coordsTranslation.row;
        m_externCoords.col += coordsTranslation.col;

        return m_externCoords;
    }
}
