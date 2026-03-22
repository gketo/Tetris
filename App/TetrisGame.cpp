#include "TetrisGame.h"

namespace Game {

    bool TetrisGame::init(Core::EventManager<Action>& em)
    {
        mapKeys(em);
        return true;
    }

    void TetrisGame::mapKeys(Core::EventManager<Action>& em)
    {
        em.mapKey(Core::KeyCode::ctrl_p, Action::PAUSE);
        em.mapKey(Core::KeyCode::spacebar, Action::PLAY);
        em.mapKey(Core::KeyCode::ctrl_q, Action::QUIT);
    }

    bool TetrisGame::update(Action action)
    {
        if (!m_isRunning && action != Action::PLAY)
            return false;

        switch (action)
        {
        case Action::PAUSE:
            m_isRunning = false;
            return true;
        case Action::PLAY:
            std::cout << "launching game\n";
            m_isRunning = true;
            return true;
        case Action::QUIT:
            m_isRunning = false;
            return true;
        default:
            return false;
        }
        return false;
    }
}