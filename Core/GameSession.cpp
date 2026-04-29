#include "GameSession.h"

#include "CommandVariant.h"
#include "DataVariant.h"
#include "EventManager.h"
#include "GameStateGameover.h"
#include "GameStateLoading.h"
#include "GameType.h"
#include "IGame.h"
#include "TetrisGame.h"

#include <memory>
#include <string>
#include <vector>

namespace Core::Session {

    bool GameSession::handleEvent(const CommandVariant& e)
    {
        return m_sm.handleEvent(e);
    }
    
    void GameSession::collectRenderData(RenderQueue& out) const
    {
        m_sm.collectRenderData(out);
    }

    void GameSession::loadGame(Game::GameType gameType)
    {
        LOG_DEBUG("[GameSession] Trying to load <%s> as current game...", Game::gametype_to_string(gameType)); 
        m_sm.clearAndPush(std::make_unique<GameStateLoading>(*this, gameType));
    }

    Game::IGame* GameSession::getGame() const
    {
        return m_game.get();
    }

    void GameSession::setGame(std::unique_ptr<Game::IGame> game)
	{
        if (!game)
        {
            throw std::invalid_argument("GameSession setGame() received null game");
        }

		m_game = std::move(game);
	}

	void GameSession::clear()
	{
		m_game = nullptr;
        m_sm.clear();
	}

    void GameSession::update()
	{
        m_sm.update();
	}

	bool GameSession::shouldExit()
	{
		return dynamic_cast<const GameStateGameover*>(m_sm.getState()) ||
            dynamic_cast<const GameStateQuitted*>(m_sm.getState());
	}
}