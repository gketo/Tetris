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
        if (auto ge = dynamic_cast<GameEngine*>(m_context))
        {
            ge->m_renderer->clearScreen();
        }
    }

    inline void StateInitialized::exit()
    {
        LOG_DEBUG("[GameEngineSM] StateInitialized : exit()...");
        // do nothing
    }

    inline void StateInitialized::update()
    {
        LOG_DEBUG("[GameEngineSM] StateInitialized : update()...");
        if (auto ge = dynamic_cast<GameEngine*>(m_context))
        {
            m_isFinished = true;
            ge->m_sm.push(std::make_unique<StateRunning>(m_context));
        }
    }

    inline bool StateInitialized::isFinished() const
    {
        return m_isFinished;
    }

}