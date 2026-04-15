#pragma once

#include "GameEngine.h"
#include "IContext.h"
#include "IState.h"
#include "StateDisplayRules.h"

namespace Core::Engine {

    class StateInitialized : public IState 
    {
    public:
        StateInitialized(IContext* context) : IState(context) {}

        void enter() override;
        void exit() override;
        void update() override;

        bool isFinished() const override;
    };

    inline void StateInitialized::enter()
    {
        LOG_DEBUG("[GameEngineSM] StateInitialized : enter()...");
        // do nothing
    }

    inline void StateInitialized::exit()
    {
        LOG_DEBUG("[GameEngineSM] StateInitialized : exit()...");
        // do nothing
    }

    inline void StateInitialized::update()
    {
        LOG_DEBUG("[GameEngineSM] StateInitialized : update()...");
        // do nothing
        if (auto ge = dynamic_cast<GameEngine*>(m_context))
        {
            ge->m_sm.setNextState(std::make_unique<StateDisplayRules>(m_context));
        }

    }

    inline bool StateInitialized::isFinished() const
    {
        return true;
    }

}