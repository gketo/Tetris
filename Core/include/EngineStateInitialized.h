#pragma once

#include "EngineStateRunning.h"
#include "GameType.h"
#include "IEngineStateContext.h"
#include "IState.h"
#include "Logger.h"

namespace Core::Engine {

    class EngineStateInitialized : public IState<IEngineStateContext>
    {
    public:
        EngineStateInitialized(IEngineStateContext& context, Game::GameType gameType) 
        : IState(context)
        , m_gameType{ gameType }
        {}

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;

    private:
        Game::GameType m_gameType;
    };

    inline void EngineStateInitialized::enter()
    {
        LOG_DEBUG("[GameEngineSM] EngineStateInitialized : enter()...");
        m_context.getRenderer().clearScreen();
        m_context.getGameSession().loadGame(m_gameType);
        m_isFinished = true;
        m_context.getStateMachine().push(std::make_unique<EngineStateRunning>(m_context));
    }

    inline void EngineStateInitialized::update()
    {
        LOG_EXTRA("[GameEngineSM] EngineStateInitialized : update()...");
        // do nothing
    }

    inline void EngineStateInitialized::exit()
    {
        LOG_DEBUG("[GameEngineSM] EngineStateInitialized : exit()...");
        // do nothing
    }

    inline bool EngineStateInitialized::isFinished() const
    {
        return m_isFinished;
    }

}