#include "GameMaster.h"

#include "ActionVariant.h"
#include "DataVariant.h"
#include "EventManager.h"
#include "GameType.h"
#include "IGame.h"
#include "TetrisGame.h"

#include <memory>
#include <string>

namespace Core {

	bool GameMaster::update(const ActionVariant& action)
	{
		return m_currentGame->update(action);
	}

	void GameMaster::setCurrentGame(Game::GameType gameType)
	{
		LOG_DEBUG("[GameMaster] Setting <%s> as current game...", Game::gametype_to_string(gameType)); 
		switch (gameType)
		{
		case Game::GameType::TETRIS:
			m_currentGame = std::make_unique<Game::Tetris::TetrisGame>();
			break;
		case Game::GameType::TEST:
			m_currentGame = std::make_unique<Game::Tetris::TetrisGame>();
			break;
		default:
			throw std::runtime_error("GameMaster: trying to setCurrentGame() unexisting game");
			break;
		}
	}

	void GameMaster::unsetCurrentGame()
	{
		m_currentGame = nullptr;
	}

	void GameMaster::initGame(EventManager& em)
	{
		LOG_DEBUG("[GameMaster] Initializing current game..."); 
		m_currentGame->init(em);
	}

	void GameMaster::resetGame()
	{
		m_currentGame->reset();
	}

	bool GameMaster::isGameOver()
	{
		return m_currentGame->isGameOver();
	}

	const Game::Rules& GameMaster::getRules() const
	{
		return m_currentGame->getRules();
	}

 	std::unique_ptr<DataVariant> GameMaster::getRenderData() const
	{
		return std::make_unique<DataVariant>(m_currentGame->getData());
	}


	// void GameMaster::onTerminate() noexcept
	// {
	// 	LOG_DEBUG("[GameMaster] Shutting down game...");
	// 	m_currentGame->terminate();
	// }

	// void GameMaster::onQuit() noexcept
	// {
	// 	LOG_DEBUG("[GameMaster] Quiting...");
	// 	// ex save data here
	// }
}