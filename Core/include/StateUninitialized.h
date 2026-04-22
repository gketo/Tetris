#pragma once

#include "GameEngine.h"
#include "IContext.h"
#include "IState.h"

namespace Core::Engine {

    class StateUninitialized : public IState 
    {
    public:
        StateUninitialized(IContext* context) : IState(context) {}

        void enter() override;
        void exit() override;
        void update() override;

        bool isFinished() const override;
    };

    inline void StateUninitialized::enter()
    {
        LOG_DEBUG("[GameEngineSM] StateUninitialized : enter()...");
        // this one is always finished to allow transition
        m_isFinished = true;
    }

    inline void StateUninitialized::exit()
    {
        LOG_DEBUG("[GameEngineSM] StateUninitialized : exit()...");
        // do nothing
    }

    inline void StateUninitialized::update()
    {
        LOG_DEBUG("[GameEngineSM] StateUninitialized : update()...");
        // do nothing
    }

    inline bool StateUninitialized::isFinished() const
    {
        return m_isFinished;
    }
}