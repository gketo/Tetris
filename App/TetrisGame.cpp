#include "TetrisGame.h"

#include "ActionVariant.h"
#include "DataVariant.h"
#include "DeviceEvent.h"
#include "EventManager.h"
#include "IGame.h"
#include "Logger.h"
#include "RulesData.h"
#include "TetrisAction.h"

#include <string>
#include <variant>

// dbg debug
#include "DebugHelpers.h"

namespace Game::Tetris {

    void TetrisGame::init(Core::EventManager& em)
    {
		LOG_DEBUG("[TetrisGame] Initializing...");
        bindKeys(em);
        setRules();
        // dbg
        setData();
    }

    void TetrisGame::reset()
    {
        // todo
    }

    void TetrisGame::bindKeys(Core::EventManager& em)
    {
		LOG_DEBUG("[TetrisGame] Binding keys...");
         
        //em.bindKey( Core::KeyCode::ARROW_UP, Core::ActionVariant{ std::in_place_type<TetrisAction>, TetrisAction::ROTATE_LEFT });
    }

    void TetrisGame::setRules()
    {
        m_rules = RulesData{
            "Welcome to Tetris, here are the rules :)",
            "- Move pieces left/right using arrow keys",
            "- Rotate pieces using up arrow",
            "- Drop pieces faster using down arrow",
            "- Clear lines to score points",
            "- Press P to pause",
            "- Then press R to resume or press Q to quit",
            "Ready to start ? Press ENTER to play :D (already leaving ? :( Press Q))"
        };
    }

    bool TetrisGame::update(Core::ActionVariant action)
    {
        return false;
    }

    bool TetrisGame::isGameOver() const
    {
        return false;
    }

    //debug 
    void TetrisGame::setData()
    {
        if (isGameOver())
        {
            //todo
            m_data = Core::DataVariant{
                std::in_place_type<Core::Grid2D::Frame2D<char>>,
                Core::Debug::dbg_createEmptyFrame<char>(20, 50)
            };
        }

        // dbg debug
        m_data = Core::DataVariant{
                std::in_place_type<Core::Grid2D::Frame2D<char>>,
                Core::Debug::dbg_createComprehensiveTestFrame<char>(20, 50)
            };
    }

    const Core::DataVariant& TetrisGame::getData() const
    {
        return m_data;
    }

}