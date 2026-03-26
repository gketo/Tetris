#include "GameMaster.h"

#include "Action.h"
#include "EventManager.h"

#include <string>

namespace Core {

	void GameMaster::init(EventManager& em)
	{
		LOG_DEBUG("[GameMaster] Initializing...");
		m_currentGame.init(em);
	}

	std::string GameMaster::getRules()
	{
		return m_currentGame.rules();
	}

	bool GameMaster::update(Action action)
	{
		return m_currentGame.update(action);
	}

	void GameMaster::resume()
	{
		m_currentGame.resume();
	}

	void GameMaster::pause()
	{
		m_currentGame.pause();
	}

	void GameMaster::stop()
	{
		m_currentGame.stop();
	}

	bool GameMaster::isRunning()
	{
		return m_currentGame.isRunning();
	}

	bool GameMaster::isPaused()
	{
		return m_currentGame.isPaused();
	}
}