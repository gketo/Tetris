#pragma once

#include "GameEngine.h"
#include "IContext.h"
#include "IState.h"
#include "Logger.h"
#include "StateTerminated.h"

namespace Core::Engine {

    class StateQuitted : public IState
    {
    public:
        StateQuitted(IContext* context) : IState(context) {}

        void enter() override;
        void exit() override;
        void update() override;

        bool isFinished() const override;
    };

    inline void StateQuitted::enter()
    {
        // do nothing
        LOG_DEBUG("[GameEngineSM] StateQuitted : enter()...");
        if (auto ge = dynamic_cast<GameEngine*>(m_context))
        {
            ge->save();
        }
    }

    inline void StateQuitted::exit() 
    { 
        LOG_DEBUG("[GameEngineSM] StateQuitted : exit()...");
        // do nothing
    }

    inline void StateQuitted::update() 
    { 
        LOG_DEBUG("[GameEngineSM] StateQuitted : update()...");
        // do nothing
    }

    inline bool StateQuitted::isFinished() const 
    { 
        return true; 
    }

}