#pragma once

// ==================== Includes ====================
#include "App/Game/GameType.h"

#include "Core/Engine/EngineSM/EngineStateContext.h"

#include "Core/GameController/GameController.h"

#include "Core/Menu/Menu.h"

#include "Core/StateMachine/StateMachine.h"

// ==================== Includes ====================
#include <string>

namespace Core {
    class EventManager; // forward declaration
    class IRenderer;    // forward declaration
}

namespace Core::Engine {

	class Engine : public EngineStateContext
	{
	public:
		Engine(EventManager& em, IRenderer& re)
			: m_eventManager{ em }
            , m_gameSession{ em }
			, m_renderer{ re }
		{}
        
        // EngineStateContext
        EventManager& getEventManager() override { return m_eventManager; }
        Core::Session::GameController& getGameController() override { return m_gameSession; }
        IRenderer& getRenderer() override { return m_renderer; }
        StateMachine<EngineStateContext>& getStateMachine() override { return m_sm; }

		void init(App::Game::GameType gameType);
		void run();
		void reset();
        void terminate();

	private: // todo ensure right order destruction because renderer owns terminal and evenmanager uses it
        StateMachine<EngineStateContext> m_sm;
		EventManager& m_eventManager;
		Core::Session::GameController m_gameSession;
        IRenderer& m_renderer;
		Menu m_menu;
		
		bool shouldExit();

		void pollInputEvents();
        void update();
		void render();

		void save();
	};

}