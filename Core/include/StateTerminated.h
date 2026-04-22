#pragma once

#include "GameEngine.h"
#include "IContext.h"
#include "IState.h"
#include "Logger.h"

namespace Core::Engine {

    class StateTerminated : public IState 
    {
    public:
        StateTerminated(IContext* context) : IState(context) {}

        void enter() override;
        void exit() override;
        void update() override;

        bool isFinished() const override;
    };

    inline void StateTerminated::enter()
    {
        LOG_DEBUG("[GameEngineSM] StateTerminated : enter()...");
        if (auto ge = dynamic_cast<GameEngine*>(m_context))
        {
		    ge->m_renderer->terminate();
            m_isFinished = true;
        }
    }

    inline void StateTerminated::exit() 
    { 
        LOG_DEBUG("[GameEngineSM] StateTerminated : exit()...");
        // do nothing
    }

    inline void StateTerminated::update() 
    { 
        LOG_DEBUG("[GameEngineSM] StateTerminated : update()...");
        // do nothing
    }

    inline bool StateTerminated::isFinished() const 
    { 
        return m_isFinished;
    }

}