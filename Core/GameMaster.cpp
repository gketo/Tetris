#include "GameMaster.h"

namespace Core {

	bool GameMaster::init(Core::EventManager<Game::Action>& em)
	{
		return m_currentGame.init(em);
	}

	bool GameMaster::isRunning()
	{
		return m_currentGame.isRunning();
	}

	bool GameMaster::update(Game::Action action)
	{
		return m_currentGame.update(action);
	}

}