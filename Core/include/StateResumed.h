#pragma once

#include "IContext.h"
#include "GameEngine.h"
#include "IState.h"
#include "StateRunning.h"

namespace Core::Engine {

    class StateResumed : public IState 
    {
    public:
        StateResumed(IContext* context) : IState(context) {}

        void enter() override;
        void exit() override;
        void update() override;

        bool isFinished() const override;
    };

    inline void StateResumed::enter()
    {
        LOG_DEBUG("[GameEngineSM] StateResumed : enter()...");
    }

    inline void StateResumed::exit()
    {
        LOG_DEBUG("[GameEngineSM] StateResumed : exit()...");
        // do nothing
    }

    inline void StateResumed::update()
    {
        LOG_DEBUG("[GameEngineSM] StateResumed : update()...");
        if (auto ge = dynamic_cast<GameEngine*>(m_context))
        {
            ge->m_sm.setNextState(std::make_unique<StateRunning>(m_context));
        }
    }

    inline bool StateResumed::isFinished() const
    {
        return true;
    }
}