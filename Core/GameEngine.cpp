#include "GameEngine.h"

#include "EventManager.h"
#include "GameMaster.h"
#include "Logger.h"
#include "Menu.h"
#include "StateUninitialized.h"
#include "StateInitialized.h"
#include "StateQuitted.h"

#include <memory>
#include <string>

namespace Core::Engine {

    void GameEngine::init(Game::GameType gameType)
	{

		LOG_DEBUG("[GameEngine] Initializing...");        

        m_eventManager->clearInputBindings();
        m_gameMaster.setCurrentGame(gameType);
        m_gameMaster.initGame(*m_eventManager);

        m_sm.push(std::make_unique<StateInitialized>(this));
    }

	void GameEngine::run()
	{		
        if (dynamic_cast<const StateUninitialized*>(m_sm.getState()))
		{
			throw std::runtime_error("GameEngine: run() called but Engine is uninitialized");
		}

		LOG_DEBUG("[GameEngine] Engine running...");

		// main loop on game
		while (!shouldExit())
		{
            LOG_DEBUG("LOOOP");
			pollEvents();
            update();
            render();
		}
	}

    void GameEngine::reset()
	{
		LOG_DEBUG("[GameEngine] Reset requested... ========TODO");
		m_eventManager->clearPendingEvents();
		m_gameMaster.unsetCurrentGame();
		m_menu.clear();
	}

    void GameEngine::terminate()
    {
        // todo
		LOG_DEBUG("[GameEngine] Termination requested... ========TODO");
        m_eventManager->clearPendingEvents();
		m_gameMaster.unsetCurrentGame();
		m_menu.clear();
    }

	bool GameEngine::shouldExit()
	{
		return m_gameMaster.isGameOver() || dynamic_cast<const StateQuitted*>(m_sm.getState());
	}

	void GameEngine::pollEvents()
	{
		// get events from event manager (controller)
		m_eventManager->pollEvents();
	}

    void GameEngine::update()
    {
        m_sm.update();
    }

    //todo safe rendering with data empty
	void GameEngine::render()
	{
        m_renderer->render(); 
    }

	void GameEngine::save()
	{
		LOG_DEBUG("[GameEngine] Save requested... ========TODO");
	}

}
