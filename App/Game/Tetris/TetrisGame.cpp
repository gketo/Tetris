#include "App/Game/Tetris/TetrisGame.h"

#include "Core/Event/CommandVariant.h"
#include "Core/Event/Events/DeviceEvent.h"
#include "Core/Event/Manager/EventManager.h"
#include "Core/Game/IGame.h"
#include "Core/Utils/Logger.h"
#include "App/Game/Tetris/TetrisBoard.h"
#include "App/Game/Tetris/TetrisCommand.h"
#include "App/Game/Tetris/Tetromino.h"
#include "Core/Render/RenderDataVariant.h"

#include <string>
#include <variant>

// dbg debug
// #include "Core/Debug/DebugHelpers.h"

namespace App::Game::Tetris {

    void TetrisGame::init()
    {
		LOG_DEBUG("[TetrisGame] Initializing...");

        m_board.init();

        size_t spawnRow = 20;
        m_deck = createTetrominoDeck(spawnRow);
        m_deck.shuffle();
        m_board.setActiveTetromino(m_deck.draw());
    }

    void TetrisGame::update()
    {
        // draw a new tetromino if requested
        if (m_board.requestTetromino())
        {
            if (m_deck.empty())
            {
                m_deck.reset();
            }

            m_board.setActiveTetromino(m_deck.draw());
        }
    }

    void TetrisGame::reset()
    {
		LOG_DEBUG("[TetrisGame] Reset...");
        m_deck.reset();
    }

    bool TetrisGame::isGameOver() const
    {
        return false;
    }

    bool TetrisGame::handleEvent(Core::CommandVariant e)
    {
        if (auto* action = std::get_if<TetrisCommand>(&e))
        {
            switch (*action)
            {
            case TetrisCommand::TRANSLATE_LEFT:
            case TetrisCommand::TRANSLATE_RIGHT:
            case TetrisCommand::SOFT_DROP:
            case TetrisCommand::ROTATE_CLOCKWISE:
            case TetrisCommand::ROTATE_LEFT:
                m_board.rotateActiveLeft();
                return true;
            case TetrisCommand::ROTATE_RIGHT:
                m_board.rotateActiveRight();
                return true;
            case TetrisCommand::HARD_DROP:
            case TetrisCommand::HOLD:
            default:
                LOG_ERROR("[TetrisGame] TetrisCommand skipped");
                return false;
            }
        }
        return false;
    }

    void TetrisGame::collectRenderData(Core::RenderQueue& out) const
    {
        if (isGameOver())
        {
            out.submit(std::make_unique<Core::RenderDataVariant>(m_board.board()));
            return;
        }

        out.submit(std::make_unique<Core::RenderDataVariant>(m_board.board()));
        // std::cout << m_board.board().data().toString().c_str();
        out.submit(std::make_unique<Core::RenderDataVariant>(TetrisGameHelpCmds));
    }
    
}