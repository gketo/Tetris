#pragma once

// ==================== Includes ====================
#include "App/Game/GameType.h"

#include "Core/Event/CommandVariant.h"

#include "Core/Game/IGame.h"

#include "Core/GameController/GameControllerSM/GameStateContext.h"

#include "Core/StateMachine/StateMachine.h"

// ==================== Includes ====================
#include <memory>

namespace Core {
	class EventManager; // forward declaration
}

namespace Core::Session {

	class GameController : public GameStateContext
	{
	public:
        GameController(EventManager& em)
        : m_eventManager{ em }
        {}

        // GameStateContext
        GameController& getGameController() override { return *this; }
        EventManager& getEventManager() override { return m_eventManager; }
        StateMachine<GameStateContext>& getStateMachine() override { return m_sm; }

        bool handleEvent(CommandVariant e);
        void collectRenderData(RenderQueue& out) const;

        void loadGame(App::Game::GameType gameType);
        App::Game::IGame* getGame() const;
		void setGame(std::unique_ptr<App::Game::IGame> game);
        
		void clear();
		void update();
		bool shouldExit();

	private:
        StateMachine<GameStateContext> m_sm;
		std::unique_ptr<App::Game::IGame> m_game;
        EventManager& m_eventManager;
	};

}
