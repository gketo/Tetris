#include "TetrisGame.h"

#include "DeviceEvent.h"
#include "EventManager.h"
#include "Game.h"
#include "Logger.h"
#include "TetrisAction.h"

#include <string>

namespace Tetris {

    void TetrisGame::bindKeys(Core::EventManager& em)
    {
		LOG_DEBUG("[TetrisGame] Binding keys...");
        em.bindKey(Core::KeyCode::arrow_up, TetrisAction::ROTATE_LEFT);
    }

    void TetrisGame::init(Core::EventManager& em)
    {
		LOG_DEBUG("[TetrisGame] Initializing...");
        bindKeys(em);
    }

    std::string TetrisGame::rules()
    {
        return
            "Welcome to Tetris, here are the rules :)\n"
            "- Move pieces left/right using arrow keys\n"
            "- Rotate pieces using up arrow\n"
            "- Drop pieces faster using down arrow\n"
            "- Clear lines to score points\n"
            "- Press Ctrl+P to pause\n"
            "- Press Ctrl+Q to quit\n"
            "Ready to start ? Press spacebar to play :D\n";
    }

    bool TetrisGame::update(Core::Action action)
    {
        return false;
    }

    bool TetrisGame::isRunning() const
    {
        return true && !m_stopRequested;
    }

}