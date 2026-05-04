#pragma once

#include "IGameStateContext.h"
#include "IState.h"
#include "Logger.h"

namespace Core::Session {

    class GameStateQuitted : public IState<IGameStateContext>
    {
    public:
        GameStateQuitted(IGameStateContext& context)
        : IState(context)
        {}

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;
    };

    inline void GameStateQuitted::enter()
    {
        LOG_DEBUG("[GameSessionSM] GameStateQuitted : enter()...");
        // do nothing
    }

    inline void GameStateQuitted::update() 
    { 
        LOG_EXTRA("[GameSessionSM] GameStateQuitted : update()...");
        // do nothing
    }

    inline void GameStateQuitted::exit() 
    { 
        LOG_DEBUG("[GameSessionSM] GameStateQuitted : exit()...");
        // do nothing
    }

    inline bool GameStateQuitted::isFinished() const 
    { 
        return m_isFinished;
    }
}