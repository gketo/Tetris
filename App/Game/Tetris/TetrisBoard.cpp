#include "App/Game/Tetris/TetrisBoard.h"

#include "App/Game/Tetris/Tetromino.h"
#include "Core/Containers/Board/Board.h"
#include "Core/Containers/Board/Cell.h"
#include "Core/Containers/Board/CellVisual.h"


#include <utility>

namespace App::Game::Tetris {

    void TetrisBoard::init()
    {
		LOG_DEBUG("[TetrisBoard] Initializing...");

        Core::Container::GlyphElement ge{ U'·' };
        Core::Container::RenderElement re{ ge };
        m_board.reset( Core::Container::Cell{ re } );        
    }

    Core::Container::Board TetrisBoard::board() const
    {
        auto board = m_board;
        if (m_activeTetromino)
        {
            for (const auto& block : m_activeTetromino->getBlocks())
            {
                Core::Container::CellVisual visual;
                visual.elements.emplace_back(Core::Container::BlockElement{ block.color() });

                Core::Container::Cell cell;
                cell.visual = visual;

                board.data().set(block.row(), block.col(), cell);
                board.data().at(block.row(), block.col()).claim();
            }
        }

        return board;
    }

    void TetrisBoard::setActiveTetromino(Tetromino tetromino)
    {
        m_activeTetromino = std::move(tetromino);
    }

    bool TetrisBoard::requestTetromino() const
    {
        return m_activeTetromino.has_value();
    }

    void TetrisBoard::translateLeftActive()
    {
        if (m_activeTetromino)
        {
            m_activeTetromino->translateLeft();
        }
    }

    void TetrisBoard::translateRightActive()
    {
        if (m_activeTetromino)
        {
            m_activeTetromino->translateRight();
        }
    }

    void TetrisBoard::softDropActive()
    {
        
    }

    void TetrisBoard::rotateActiveClockwise()
    {

    }

    void TetrisBoard::rotateActiveLeft()
    {
        if (m_activeTetromino)
        {
            m_activeTetromino->rotateLeft();
        }
    }

    void TetrisBoard::rotateActiveRight()
    {
        if (m_activeTetromino)
        {
            m_activeTetromino->rotateRight();
        }
    }
    
    void TetrisBoard::hardDropActive()
    {

    }

    void TetrisBoard::holdActive()
    {

    }

}