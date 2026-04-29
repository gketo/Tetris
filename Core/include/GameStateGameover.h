#pragma once

#include "IGameStateContext.h"
#include "IState.h"
#include "Logger.h"

namespace Core::Session {

    class GameStateGameover : public IState<IGameStateContext>
    {
    public:
        GameStateGameover(IGameStateContext& context) : IState(context) {}

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;
    };

    inline void GameStateGameover::enter()
    {
        LOG_DEBUG("[GameSessionSM] GameStateGameover : enter()...");
        // do nothing
    }

    inline void GameStateGameover::update() 
    { 
        LOG_EXTRA("[GameSessionSM] GameStateGameover : update()...");
        // do nothing
    }

    inline void GameStateGameover::exit() 
    { 
        LOG_DEBUG("[GameSessionSM] GameStateGameover : exit()...");
        // do nothing
    }

    inline bool GameStateGameover::isFinished() const 
    { 
        return m_isFinished;
    }
}