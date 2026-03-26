#pragma once

#include "Game.h"
#include "TetrisAction.h"

#include <string>

namespace Core {
    class EventManager; // forward declaration
}

namespace Tetris {

	class TetrisGame : public Game::Game
	{
	public:
		void bindKeys(Core::EventManager& em) override;
        void init(Core::EventManager& em) override;
		std::string rules() override;
        bool update(Core::Action action) override;
		bool isRunning() const override;
	};

}