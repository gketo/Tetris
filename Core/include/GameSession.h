#pragma once

#include "CommandVariant.h"
#include "GameType.h"
#include "IGame.h"
#include "IGameStateContext.h"
#include "StateMachine.h"

#include <memory>

namespace Core {
	class EventManager; // forward declaration
}

namespace Core::Session {

	class GameSession : public IGameStateContext
	{
	public:
        GameSession(EventManager& em)
        : m_eventManager{ em }
        {}

        GameSession& getGameSession() override { return *this; }
        EventManager& getEventManager() override { return m_eventManager; }
        StateMachine<IGameStateContext>& getStateMachine() override { return m_sm; }

        bool handleEvent(const CommandVariant& e);
        void collectRenderData(RenderQueue& out) const;

        void loadGame(Game::GameType gameType);
        Game::IGame* getGame() const;
		void setGame(std::unique_ptr<Game::IGame> game);
        
		void clear();
		void update();
		bool shouldExit();

	private:
        StateMachine<IGameStateContext> m_sm;
		std::unique_ptr<Game::IGame> m_game{ nullptr };
        EventManager& m_eventManager;
	};

}
