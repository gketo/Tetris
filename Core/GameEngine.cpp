#include "GameEngine.h"

#include "EngineStateInitialized.h"
#include "EngineStateTerminated.h"
#include "EventManager.h"
#include "GameSession.h"
#include "IRenderer.h"
#include "Logger.h"
#include "Menu.h"
#include "StateMachine.h"

#include <memory>
#include <stdexcept>

namespace Core::Engine {

    void GameEngine::init(Game::GameType gameType)
	{
		LOG_DEBUG("[GameEngine] Initializing...");  
        m_eventManager->unbindAllInputs();
        m_sm.clearAndPush(std::make_unique<EngineStateInitialized>(*this, gameType));
    }

	void GameEngine::run()
	{		
        if (!dynamic_cast<const EngineStateInitialized*>(m_sm.getState()))
		{
			throw std::runtime_error("GameEngine: run() called but Engine is not initialized");
		}

		LOG_DEBUG("[GameEngine] Engine run()...");

		// main loop on game
        LOG_DEBUG("LOOOP");
		while (!shouldExit())
		{
			pollInputEvents();
            update();
            render();
		}
    
        save();
        terminate();
	}

    void GameEngine::reset()
	{
		LOG_DEBUG("[GameEngine] Reset requested... ========TODO");
		m_gameSession.clear();
        m_sm.clear();
        m_eventManager->unbindAllInputs();
		m_eventManager->clearInputEvents();
		m_menu.clear();
	}

    void GameEngine::terminate()
    {
        // todo
		LOG_DEBUG("[GameEngine] Termination requested... ========TODO");
        reset();
    }

	bool GameEngine::shouldExit()
	{
		return m_gameSession.shouldExit() || dynamic_cast<const EngineStateTerminated*>(m_sm.getState());
	}

	void GameEngine::pollInputEvents()
	{
		// get events from event manager (controller)
		LOG_EXTRA("[GameEngine] Engine pollInputEvents()...");
		m_eventManager->pollInputEvents();
        while (auto eventOpt = m_eventManager->popInputEvent())
        {
            const auto& event = *eventOpt;

            if (m_sm.handleEvent(event))
            {
		        LOG_DEBUG("[GameEngine] Event consumed by engine SM");
                continue;
            }

            if (m_gameSession.handleEvent(event))
            {
		        LOG_DEBUG("[GameEngine] Event consumed by gamesession SM");
                continue;
            }
        }
	}

    void GameEngine::update()
    {
		LOG_EXTRA("[GameEngine] Engine update()...");
        m_sm.update();
    }

    //todo safe rendering with data empty
	void GameEngine::render()
	{
		LOG_EXTRA("[GameEngine] Engine render()...");
        auto& queue = m_renderer->getRenderQueue();
        if (!m_sm.collectRenderData(queue))
        {
            m_gameSession.collectRenderData(queue);
        }

        m_renderer->render(); 
    }

	void GameEngine::save()
	{
		LOG_DEBUG("[GameEngine] Save requested... ========TODO");
	}

}
