#pragma once

#include "ActionVariant.h"
#include "DataVariant.h"
#include "GameType.h"
#include "IGame.h"

#include <map>
#include <memory>
#include <string>

namespace Game {
	class RulesData;
}

namespace Core {
	// forward declaration
	class EventManager; 
}

namespace Core {

	class GameMaster
	{
	public:
		bool update(const ActionVariant& action);

		void setCurrentGame(Game::GameType gameType);
		void unsetCurrentGame();

		void initGame(EventManager& em);
		void resetGame();
		bool isGameOver();

		std::unique_ptr<DataVariant> getRules() const;
		std::unique_ptr<DataVariant> getRenderData() const;

	private:
		std::unique_ptr<Game::IGame> m_currentGame{ nullptr };
	};

}
