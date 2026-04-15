#pragma once

#include "DataVariant.h"
#include "IGame.h"
#include "TetrisAction.h"

namespace Core {
    class EventManager; // forward declaration
}

namespace Game::Tetris {

	class TetrisGame : public IGame
	{
	public:
        void init(Core::EventManager& em) override;
		void reset() override;
		void bindKeys(Core::EventManager& em) override;
        bool update(Core::ActionVariant action) override;
		bool isGameOver() const override;

    	const Core::DataVariant& getData() const override;

	private:
		void setRules() override;
        //debug
        void setData();
	};

}