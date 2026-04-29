#pragma once

#include "GameSession.h"
#include "GameStatePlaying.h"
#include "GameType.h"
#include "IGameStateContext.h"
#include "IState.h"
#include "Logger.h"
#include "TetrisGame.h"

namespace Core::Session {

    class GameStateLoading : public IState<IGameStateContext> 
    {
    public:
        GameStateLoading(IGameStateContext& context, Game::GameType gameType)
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

    inline void GameStateLoading::enter()
    {
        LOG_DEBUG("[GameSessionSM] GameStateLoading : enter()...");
        LOG_DEBUG("[GameSessionSM] Setting <%s> as current game...", Game::gametype_to_string(m_gameType));
        auto& gm = m_context.getGameSession();
        auto& em = m_context.getEventManager();
        switch (m_gameType)
        {
        case Game::GameType::TETRIS:
        {
            auto game = std::make_unique<Game::Tetris::TetrisGame>();
            em.bindInputs(game->getBindings());
            game->init();
            gm.setGame(std::move(game));
            break;
        }
        case Game::GameType::TEST:
        {
            auto game = std::make_unique<Game::Tetris::TetrisGame>();
            game->init();
            em.bindInputs(game->getBindings());
            gm.setGame(std::move(game));
            break;
        }
        default:
            throw std::runtime_error("GameSession: trying to setCurrentGame() unexisting game");
            break;
        }

        m_isFinished = true;
        m_context.getStateMachine().push(std::make_unique<GameStatePlaying>(m_context));
    }

    inline void GameStateLoading::update()
    {
        LOG_EXTRA("[GameSessionSM] GameStateLoading : update()...");
        // do nothing
    }

    inline void GameStateLoading::exit()
    {
        LOG_DEBUG("[GameSessionSM] GameStateLoading : exit()...");
        // do nothing
    }

    inline bool GameStateLoading::isFinished() const
    {
        return m_isFinished;
    }

}