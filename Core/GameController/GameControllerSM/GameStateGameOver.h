#pragma once

// ==================== Includes ====================
#include "Core/GameController/GameControllerSM/GameStateContext.h"

#include "Core/StateMachine/IState.h"

#include "Core/Utils/Logger.h"

namespace Core::Session {

    class GameStateGameOver : public IState<GameStateContext>
    {
    public:
        GameStateGameOver(GameStateContext& context)
        : IState(context)
        {}

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;
    };

    inline void GameStateGameOver::enter()
    {
        LOG_DEBUG("[GameControllerSM] GameStateGameOver : enter()...");
        // do nothing
    }

    inline void GameStateGameOver::update() 
    { 
        LOG_EXTRA("[GameControllerSM] GameStateGameOver : Updating...");
        // do nothing
    }

    inline void GameStateGameOver::exit() 
    { 
        LOG_DEBUG("[GameControllerSM] GameStateGameOver : exit()...");
        // do nothing
    }

    inline bool GameStateGameOver::isFinished() const 
    { 
        return m_isFinished;
    }
}