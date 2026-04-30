#pragma once

#include "IGameStateContext.h"
#include "IState.h"
#include "Logger.h"

namespace Core::Session {

    class GameStateGameOver : public IState<IGameStateContext>
    {
    public:
        GameStateGameOver(IGameStateContext& context) : IState(context) {}

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;
    };

    inline void GameStateGameOver::enter()
    {
        LOG_DEBUG("[GameSessionSM] GameStateGameOver : enter()...");
        // do nothing
    }

    inline void GameStateGameOver::update() 
    { 
        LOG_EXTRA("[GameSessionSM] GameStateGameOver : update()...");
        // do nothing
    }

    inline void GameStateGameOver::exit() 
    { 
        LOG_DEBUG("[GameSessionSM] GameStateGameOver : exit()...");
        // do nothing
    }

    inline bool GameStateGameOver::isFinished() const 
    { 
        return m_isFinished;
    }
}