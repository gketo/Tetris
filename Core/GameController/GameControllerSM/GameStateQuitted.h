#pragma once

#include "Core/GameController/GameControllerSM/GameStateContext.h"
#include "Core/StateMachine/IState.h"
#include "Core/Utils/Logger.h"

namespace Core::Session {

    class GameStateQuitted : public IState<GameStateContext>
    {
    public:
        GameStateQuitted(GameStateContext& context)
        : IState(context)
        {}

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;
    };

    inline void GameStateQuitted::enter()
    {
        LOG_DEBUG("[GameControllerSM] GameStateQuitted : enter()...");
        // do nothing
    }

    inline void GameStateQuitted::update() 
    { 
        LOG_EXTRA("[GameControllerSM] GameStateQuitted : Updating...");
        // do nothing
    }

    inline void GameStateQuitted::exit() 
    { 
        LOG_DEBUG("[GameControllerSM] GameStateQuitted : exit()...");
        // do nothing
    }

    inline bool GameStateQuitted::isFinished() const 
    { 
        return m_isFinished;
    }
}