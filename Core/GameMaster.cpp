#include "GameMaster.h"

#include "Action.h"
#include "EventManager.h"

#include <string>

namespace Core {

	void GameMaster::init(EventManager& em)
	{
		LOG_DEBUG("[GameMaster] Initializing..."); 
		Lifecycle::init();

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

	const IRenderable& GameMaster::getRenderData() const
	{
		return m_currentGame.getRenderData();
	}


	inline const char* GameMaster::caller() const  
    {
        return "GameMaster";
    }

	void GameMaster::onInit()
	{
		// generic init
	}

	void GameMaster::onLaunch()
	{
		LOG_DEBUG("[GameMaster] Launching game...");
		m_currentGame.launch();
	}
	
	void GameMaster::onResume()
	{
		LOG_DEBUG("[GameMaster] Resuming game...");
		m_currentGame.resume();
	}

	void GameMaster::onPause()
	{
		LOG_DEBUG("[GameMaster] Pausing game...");
		m_currentGame.pause();
	}

	void GameMaster::onTerminate() noexcept
	{
		LOG_DEBUG("[GameMaster] Shutting down game...");
		m_currentGame.terminate();
	}

	void GameMaster::onQuit() noexcept
	{
		LOG_DEBUG("[GameMaster] Quiting...");
		// ex save data here
	}

	bool GameMaster::isGameover()
	{
		return m_currentGame.isGameover();
	}
}