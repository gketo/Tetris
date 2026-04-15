#pragma once

#include "EventManager.h"
#include "GameMaster.h"
#include "IRenderer.h"
#include "Menu.h"

#include "IContext.h"
#include "IState.h"
#include "StateMachine.h"
#include "StateUninitialized.h"

#include <memory>
#include <string>

namespace Core::Engine {

    class StateUninitialized;
    class StateInitialized;
    class StateDisplayRules;
    class StateRunning;
    class StatePaused;
    class StateResumed;
    class StateQuitted;
    class StateTerminated;

	class GameEngine : public IContext
	{
        friend class StateUninitialized;
        friend class StateInitialized;
        friend class StateDisplayRules;
        friend class StateRunning;
        friend class StatePaused;
        friend class StateResumed;
        friend class StateQuitted;
        friend class StateTerminated;

	public:
		GameEngine(EventManager* em, IRenderer* re)
			: m_eventManager{ em }
			, m_renderer{ re }
		{
            m_sm.setNextState(std::make_unique<StateUninitialized>(this));
        }

		void init(Game::GameType gameType);
		void run();

	private: // todo ensure right order destruction because renderer owns terminal and evenmanager uses it
        StateMachine m_sm;

		GameMaster m_gameMaster;
		EventManager* m_eventManager{ nullptr };
		IRenderer* m_renderer{ nullptr };
		Menu m_menu;
		
		bool shouldExit();

		void pollEvents();
        void update();
		void render();

		void save();
		void reset();
	};

}