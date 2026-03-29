#pragma once

#include "Game.h"
#include "TetrisAction.h"

#include <string>

namespace Core {
    class EventManager; // forward declaration
	class IRenderable;
}

namespace Tetris {

	class TetrisGame : public Game::Game
	{
	public:
        void init(Core::EventManager& em) override;
		void bindKeys(Core::EventManager& em) override;
		std::string rules() override;
        bool update(Core::Action action) override;
		bool isGameover() const override;

        const Core::IRenderable& getRenderData() const override;
	};

}