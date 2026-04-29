#include "TetrisGame.h"

#include "CommandVariant.h"
#include "Config_AppInputBindings.h"
#include "DataVariant.h"
#include "DeviceEvent.h"
#include "EventManager.h"
#include "IGame.h"
#include "Logger.h"

#include <string>
#include <variant>

// dbg debug
#include "DebugHelpers.h"

namespace Game::Tetris {

    void TetrisGame::init()
    {
		LOG_DEBUG("[TetrisGame] Initializing...");
    }

    void TetrisGame::pause(Core::EventManager&)
    {}

    void TetrisGame::resume(Core::EventManager& em)
    {}

    void TetrisGame::reset(Core::EventManager&)
    {
        // todo
    }

    bool TetrisGame::update(Core::CommandVariant action)
    {
        return false;
    }

    bool TetrisGame::isGameOver() const
    {
        return false;
    }

    void TetrisGame::collectRenderData(Core::RenderQueue& out) const
    {
        out.submit(std::make_unique<Core::DataVariant>(m_data));
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

}