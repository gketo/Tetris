#pragma once

// ==================== Includes ====================
#include "Core/Engine/EngineCommand.h"

#include "Core/Event/CommandVariant.h"
#include "Core/Event/Binding/Config_CoreInputBindings.h"
#include "Core/Event/Manager/EventLayer.h"
#include "Core/Event/Manager/EventManager.h"

#include "Core/Game/IGame.h"

#include "Core/GameController/GameController.h"
#include "Core/GameController/GameControllerSM/GameStatePaused.h"
#include "Core/GameController/GameControllerSM/GameStateContext.h"

#include "Core/Render/RenderQueue.h"

#include "Core/StateMachine/IState.h"
#include "Core/StateMachine/StateMachine.h"

#include "Core/Utils/Logger.h"

// ==================== Includes ====================
#include <memory>

namespace Core::Session {

    class GameStatePlaying : public IState<GameStateContext>
    {
    public:
        GameStatePlaying(GameStateContext& context)
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
        LOG_EXTRA("[GameControllerSM] GameStatePlaying : handleEvent()...");
        if (auto* action = std::get_if<Core::EngineCommand>(&e))
        {
            switch (*action)
            {
            case EngineCommand::PAUSE :
                m_isFinished = true;
                m_context.getStateMachine().push(std::make_unique<GameStatePaused>(m_context));
                return true;
            default:
                LOG_ERROR("[GameControllerSM] GameStatePlaying: EngineCommand skipped");
                return false;
            }
        }
        else if (m_context.getGameController().getGame()->handleEvent(e))
        {
		    LOG_DEBUG("[GameControllerSM] Event consumed by game");
            return true;
        }
        return false;
    }

    bool GameStatePlaying::collectRenderData(RenderQueue& out) const
    {
        LOG_EXTRA("[GameControllerSM] GameStatePlaying : collectRenderData()...");
        if (auto* game = m_context.getGameController().getGame())
        {
            game->collectRenderData(out);
            return true;
        }
        return false;
    }

    inline void GameStatePlaying::enter()
    {
        LOG_DEBUG("[GameControllerSM] GameStatePlaying : enter()...");
        m_context.getEventManager().pushActiveLayer(EventLayer::GameCtrl);
        m_context.getEventManager().bindInputs(GameStatePlayingRegisteredEvents);
    }

    inline void GameStatePlaying::update()
    {
        LOG_EXTRA("[GameControllerSM] GameStatePlaying : Updating...");
        if (m_context.getGameController().getGame()->isGameOver())
        {
            m_isFinished = true;
            m_context.getStateMachine().push(std::make_unique<GameStateGameOver>(m_context));
            return;
        }
    }

    inline void GameStatePlaying::exit()
    {
        LOG_DEBUG("[GameControllerSM] GameStatePlaying : exit()...");
        m_context.getEventManager().popActiveLayer(EventLayer::GameCtrl);
        m_context.getEventManager().unbindInputs(GameStatePlayingRegisteredEvents);
    }

    inline bool GameStatePlaying::isFinished() const
    {
        return m_isFinished;
    }

    inline void GameStatePlaying::pause()
    {
        LOG_DEBUG("[GameControllerSM] GameStatePlaying : pause()...");
        m_context.getEventManager().popActiveLayer(EventLayer::GameCtrl);
        m_context.getEventManager().unbindInputs(GameStatePlayingRegisteredEvents);
        m_isFinished = true;
    }

    inline void GameStatePlaying::resume()
    {
        LOG_DEBUG("[GameControllerSM] GameStatePlaying : resume()...");
        m_context.getEventManager().pushActiveLayer(EventLayer::GameCtrl);
        m_context.getEventManager().bindInputs(GameStatePlayingRegisteredEvents);
        m_isFinished = false;
    }
}