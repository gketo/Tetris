#include "Core/Engine/Engine.h"

// ==================== Includes ====================
#include "Core/Engine/EngineSM/EngineStateInitialized.h"
#include "Core/Engine/EngineSM/EngineStateTerminated.h"

#include "Core/Event/Manager/EventManager.h"

#include "Core/GameController/GameController.h"

#include "Core/Menu/Menu.h"

#include "Core/Render/IRenderer.h"

#include "Core/StateMachine/StateMachine.h"

#include "Core/Utils/Logger.h"

// ==================== Includes ====================
#include <memory>
#include <stdexcept>

namespace Core::Engine {

    void Engine::init(App::Game::GameType gameType)
	{
		LOG_DEBUG("[Engine] Initializing...");  
        m_eventManager.unbindAllInputs();
        m_sm.clearAndPush(std::make_unique<EngineStateInitialized>(*this, gameType));
    }

	void Engine::run()
	{		
        if (!dynamic_cast<const EngineStateInitialized*>(m_sm.getState()))
		{
			throw std::runtime_error("[Engine] run() called but Engine is not initialized");
		}

		LOG_DEBUG("[Engine] Engine run()...");

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

    void Engine::reset()
	{
		LOG_DEBUG("[Engine] Reset requested... ========TODO");
		m_gameSession.clear();
        m_sm.clear();
        m_eventManager.unbindAllInputs();
		m_eventManager.clearInputEvents();
		m_menu.clear();
	}

    void Engine::terminate()
    {
        // todo
		LOG_DEBUG("[Engine] Termination requested... ========TODO");
        reset();
    }

	bool Engine::shouldExit()
	{
		return m_gameSession.shouldExit() || dynamic_cast<const EngineStateTerminated*>(m_sm.getState());
	}

	void Engine::pollInputEvents()
	{
		// get events from event manager (controller)
		LOG_EXTRA("[Engine] Engine pollInputEvents()...");
		m_eventManager.pollInputEvents();
        while (auto eventOpt = m_eventManager.popInputEvent())
        {
            const auto& event = *eventOpt;

            if (m_sm.handleEvent(event))
            {
		        LOG_DEBUG("[Engine] Event consumed by engine SM");
                continue;
            }

            if (m_gameSession.handleEvent(event))
            {
		        LOG_DEBUG("[Engine] Event consumed by gamesession SM");
                continue;
            }
        }
	}

    void Engine::update()
    {
		LOG_EXTRA("[Engine] Engine Updating...");
        m_sm.update();
    }

    //todo safe rendering with data empty
	void Engine::render()
	{
		LOG_EXTRA("[Engine] Engine render()...");
        auto& queue = m_renderer.getRenderQueue();
        queue.clearPendingData();
        if (!m_sm.collectRenderData(queue))
        {
            m_gameSession.collectRenderData(queue);
        }

        m_renderer.render(); 
    }

	void Engine::save()
	{
		LOG_DEBUG("[Engine] Save requested... ========TODO");
	}

}
