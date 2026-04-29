#pragma once

#include "CommandVariant.h"
#include "DataVariant.h"
#include "DeviceEvent.h"
#include "DeviceType.h"
#include "EventLayer.h"
#include "IGame.h"
#include "InputBinding.h"
#include "KeyCode.h"
#include "SourceType.h"
#include "TetrisCommand.h"

#include <vector>

namespace Core {
    class EventManager; // forward declaration
}

namespace Game::Tetris {

    inline const std::vector<Core::InputBinding> TetrisGameRegisteredEvents
    {
        // Keyboard
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::MOVE_LEFT }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::ARROW_LEFT },
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::MOVE_RIGHT }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::ARROW_RIGHT },
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::SOFT_DROP }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::ARROW_DOWN },
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::ROTATE_CLOCKWISE }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::ARROW_UP },
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::ROTATE_LEFT }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::CHAR, 'z' },
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::ROTATE_RIGHT }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::CHAR, 'x' },
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::HARD_DROP }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::SPACEBAR },
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::HOLD }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::CHAR, 'c' },
        //
    };

    inline const Rules& TetrisGameRules
    {
            "Tetris, here are the rules :)", // welcome msg
            { 
                "Move pieces left/right using arrow keys",
                "Rotate pieces using up arrow",
                "Drop pieces faster using down arrow",
                "Clear lines to score points",
                "Press P to pause",
            }, // rules
            "Press ENTER and let's play :D" // commands msg
    };

	class TetrisGame : public IGame
	{
	public:
        TetrisGame() : IGame{ 24, 20 } {/* dbg */ setData();}

        void init() override;
        void pause(Core::EventManager&) override;
        void resume(Core::EventManager& em) override;
		void reset(Core::EventManager&) override;
        bool update(Core::CommandVariant action) override;
		bool isGameOver() const override;

        void collectRenderData(Core::RenderQueue& out) const override;

        const Rules& getRules() const override { return TetrisGameRules; }
        const std::vector<Core::InputBinding>& getBindings() const override { return TetrisGameRegisteredEvents; }

        private:
        //debug
        void setData();
	};

}