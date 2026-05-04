#pragma once

#include "CommandVariant.h"
#include "Config_CoreInputBindings.h"
#include "EngineCommand.h"
#include "EventLayer.h"
#include "EventManager.h"
#include "GameSession.h"
#include "GameStatePaused.h"
#include "IGame.h"
#include "IGameStateContext.h"
#include "IState.h"
#include "Logger.h"
#include "RenderQueue.h"
#include "StateMachine.h"

#include <memory>

namespace Core::Session {

    class GameStatePlaying : public IState<IGameStateContext>
    {
    public:
        GameStatePlaying(IGameStateContext& context)
        : IState(context)
        {}

        bool handleEvent(CommandVariant e) override;
        bool collectRenderData(RenderQueue& out) const override;

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;

        void pause() override;
        void resume() override;
    };

    inline bool GameStatePlaying::handleEvent(CommandVariant e)
    {
        LOG_EXTRA("[GameSessionSM] GameStatePlaying : handleEvent()...");
        if (auto* action = std::get_if<Core::EngineCommand>(&e))
        {
            switch (*action)
            {
            case EngineCommand::PAUSE :
                m_isFinished = true;
                m_context.getStateMachine().push(std::make_unique<GameStatePaused>(m_context));
                return true;
            default:
                LOG_ERROR("[GameSessionSM] GameStatePlaying: EngineCommand skipped");
                return false;
            }
        }
        return false;
    }

    bool GameStatePlaying::collectRenderData(RenderQueue& out) const
    {
        LOG_EXTRA("[GameSessionSM] GameStatePlaying : collectRenderData()...");
        if (auto* game = m_context.getGameSession().getGame())
        {
            game->collectRenderData(out);
            return true;
        }
        return false;
    }

    inline void GameStatePlaying::enter()
    {
        LOG_DEBUG("[GameSessionSM] GameStatePlaying : enter()...");
        m_context.getEventManager().pushActiveLayer(EventLayer::GameCtrl);
        m_context.getEventManager().bindInputs(GameStatePlayingRegisteredEvents);
    }

    inline void GameStatePlaying::update()
    {
        LOG_EXTRA("[GameSessionSM] GameStatePlaying : update()...");
        if (m_context.getGameSession().getGame()->isGameOver())
        {
            m_isFinished = true;
            m_context.getStateMachine().push(std::make_unique<GameStateGameOver>(m_context));
        }
    }

    inline void GameStatePlaying::exit()
    {
        LOG_DEBUG("[GameSessionSM] GameStatePlaying : exit()...");
        m_context.getEventManager().popActiveLayer(EventLayer::GameCtrl);
        m_context.getEventManager().unbindInputs(GameStatePlayingRegisteredEvents);
    }

    inline bool GameStatePlaying::isFinished() const
    {
        return m_isFinished;
    }

    inline void GameStatePlaying::pause()
    {
        LOG_DEBUG("[GameSessionSM] GameStatePlaying : pause()...");
        m_context.getEventManager().popActiveLayer(EventLayer::GameCtrl);
        m_context.getEventManager().unbindInputs(GameStatePlayingRegisteredEvents);
        m_isFinished = true;
    }

    inline void GameStatePlaying::resume()
    {
        LOG_DEBUG("[GameSessionSM] GameStatePlaying : resume()...");
        m_context.getEventManager().pushActiveLayer(EventLayer::GameCtrl);
        m_context.getEventManager().bindInputs(GameStatePlayingRegisteredEvents);
        m_isFinished = false;
    }
}