#include "App/Game/Tetris/Tetromino.h"

// ==================== Includes ====================
#include "App/Game/Tetris/TetrominoBlock.h"

#include "Core/Graphics/GfxUtils.h"

#include "Core/Lib/Matrix/Matrix.h"

#include "Core/Types/Index2D.h"

namespace App::Game::Tetris {

    namespace GfxUtils = Core::Graphics::Utils;

    void Tetromino::init()
    {
        // todo verify collision here
        for (int i = 1; i <= 4; ++i)
        {
            auto block = TetrominoBlock(i, m_shape, m_spawnLocation);
            m_blocks.emplace_back(block);
        }
    }

    void Tetromino::setSpawnLocation(const Core::Type::Index2D& topLeft)
    {
        // todo verify collision here
        for (int i = 1; i <= 4; ++i)
        {
            auto block = TetrominoBlock(i, m_shape, topLeft);
            m_blocks.emplace_back(block);
        }
        m_spawnLocation = topLeft;
    }

    void Tetromino::setColor(GfxUtils::Color c)
    { 
        for (auto& block : m_blocks)
        {
            block.setColor(c);
        } 
    }

    void Tetromino::translateLeft() //todo can i translate
    {
        // todo verify collision here
        for (auto& block : m_blocks)
        {
            block.translateLeft();
        }
    } 

    void Tetromino::translateRight()
    {
        // todo verify collision here
        for (auto& block : m_blocks)
        {
            block.translateRight();
        }
    }

    void Tetromino::rotateLeft()
    {
        auto newShape = m_shape;
        newShape.rotateLeft();
        // todo verify collision here
        
        // update each block coord
        for (auto& block : m_blocks)
        {
            block.updateCoords(m_shape, newShape);
        }

        m_shape = newShape;
    }

    void Tetromino::rotateRight()
    {
        auto newShape = m_shape;
        newShape.rotateRight();
        // todo verify collision here
        
        // update each block coord
        for (auto& block : m_blocks)
        {
            block.updateCoords(m_shape, newShape);
        }

        m_shape = newShape;
    }

    void Tetromino::animate()
    {
        if (m_isLockedDown)
        {
            return;
        }
        for (auto& block : m_blocks)
        {
            block.translateDown(m_v_speed);
        }
    }
}