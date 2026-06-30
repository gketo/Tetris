#pragma once

// ==================== Includes ====================
#include "App/Game/GameType.h"
#include "App/Game/Tetris/TetrisGame.h"

#include "Core/Event/Manager/EventManager.h"

#include "Core/GameController/GameController.h"
#include "Core/GameController/GameControllerSM/GameStatePlaying.h"
#include "Core/GameController/GameControllerSM/GameStateContext.h"

#include "Core/StateMachine/IState.h"
#include "Core/StateMachine/StateMachine.h"

#include "Core/Utils/Logger.h"

// ==================== Includes ====================
#include <memory>
#include <stdexcept>
#include <utility>

namespace Core::Session {

    class GameStateLoading : public IState<GameStateContext> 
    {
    public:
        GameStateLoading(GameStateContext& context, App::Game::GameType gameType)
        : IState(context) 
        , m_gameType{ gameType }
        {}

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;
    
    private:
        App::Game::GameType m_gameType;

    };

    inline void GameStateLoading::enter()
    {
        LOG_DEBUG("[GameControllerSM] GameStateLoading : enter()...");
        LOG_DEBUG("[GameControllerSM] Setting <%s> as current game...", App::Game::dbg_to_string(m_gameType));
        auto& gs = m_context.getGameController();
        auto& em = m_context.getEventManager();
        switch (m_gameType)
        {
        case App::Game::GameType::TETRIS:
        {
            auto game = std::make_unique<App::Game::Tetris::TetrisGame>();
            em.bindInputs(game->getBindings());
            game->init();
            gs.setGame(std::move(game));
            break;
        }
        case App::Game::GameType::TEST:
        {
            auto game = std::make_unique<App::Game::Tetris::TetrisGame>();
            game->init();
            em.bindInputs(game->getBindings());
            gs.setGame(std::move(game));
            break;
        }
        default:
            throw std::runtime_error("[GameController] GameStateLoading : enter() trying to setCurrentGame() unexisting game");
            break;
        }

        m_isFinished = true;
        m_context.getStateMachine().push(std::make_unique<GameStatePlaying>(m_context));
    }

    inline void GameStateLoading::update()
    {
        LOG_EXTRA("[GameControllerSM] GameStateLoading : Updating...");
        // do nothing
    }

    inline void GameStateLoading::exit()
    {
        LOG_DEBUG("[GameControllerSM] GameStateLoading : exit()...");
        // do nothing
    }

    inline bool GameStateLoading::isFinished() const
    {
        return m_isFinished;
    }

}