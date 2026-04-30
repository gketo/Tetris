#pragma once

#include "GameType.h"
#include "GameSession.h"
#include "IEngineStateContext.h"
#include "Menu.h"
#include "StateMachine.h"

#include <string>

namespace Core {
    class EventManager; // forward declaration
    class IRenderer;    // forward declaration
}

namespace Core::Engine {

	class GameEngine : public IEngineStateContext
	{
	public:
		GameEngine(EventManager* em, IRenderer* re)
			: m_eventManager{ em }
            , m_gameSession{ *em }
			, m_renderer{ re }
		{}
        
        EventManager& getEventManager() override { return *m_eventManager; }
        Core::Session::GameSession& getGameSession() override { return m_gameSession; }
        IRenderer& getRenderer() override { return *m_renderer; }
        StateMachine<IEngineStateContext>& getStateMachine() override { return m_sm; }

		void init(Game::GameType gameType);
		void run();
		void reset();
        void terminate();

	private: // todo ensure right order destruction because renderer owns terminal and evenmanager uses it
        StateMachine<IEngineStateContext> m_sm;
		EventManager* m_eventManager{ nullptr };
		Core::Session::GameSession m_gameSession;
        IRenderer* m_renderer{ nullptr };
		Menu m_menu;
		
		bool shouldExit();

		void pollInputEvents();
        void update();
		void render();

		void save();
	};

}