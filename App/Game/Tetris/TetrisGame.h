#pragma once

#include "Core/Event/CommandVariant.h"
#include "Core/Render/RenderDataVariant.h"
#include "Core/Help/Help.h"
#include "Core/Event/Events/DeviceEvent.h"
#include "Core/Event/Binding/DeviceType.h"
#include "Core/Event/Manager/EventLayer.h"
#include "Core/Game/IGame.h"
#include "Core/Event/Binding/InputBinding.h"
#include "Core/Event/Binding/InputType.h"
#include "Core/Event/Binding/SourceType.h"
#include "App/Game/Tetris/TetrisBoard.h"
#include "App/Game/Tetris/TetrisCommand.h"
#include "App/Game/Tetris/Tetromino.h"

#include <cstddef>
#include <vector>

namespace App::Game::Tetris {

    inline const std::vector<Core::InputBinding> TetrisGameRegisteredEvents {
        // Keyboard
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<App::Game::Tetris::TetrisCommand>, App::Game::Tetris::TetrisCommand::TRANSLATE_LEFT }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::InputType::ARROW_LEFT },
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<App::Game::Tetris::TetrisCommand>, App::Game::Tetris::TetrisCommand::TRANSLATE_RIGHT }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::InputType::ARROW_RIGHT },
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<App::Game::Tetris::TetrisCommand>, App::Game::Tetris::TetrisCommand::SOFT_DROP }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::InputType::ARROW_DOWN },
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<App::Game::Tetris::TetrisCommand>, App::Game::Tetris::TetrisCommand::ROTATE_CLOCKWISE }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::InputType::ARROW_UP },
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<App::Game::Tetris::TetrisCommand>, App::Game::Tetris::TetrisCommand::ROTATE_LEFT }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::InputType::CHAR, 'z' },
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<App::Game::Tetris::TetrisCommand>, App::Game::Tetris::TetrisCommand::ROTATE_RIGHT }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::InputType::CHAR, 'x' },
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<App::Game::Tetris::TetrisCommand>, App::Game::Tetris::TetrisCommand::HARD_DROP }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::InputType::SPACEBAR },
        Core::InputBinding{ Core::EventLayer::GameCtrl, Core::CommandVariant{ std::in_place_type<App::Game::Tetris::TetrisCommand>, App::Game::Tetris::TetrisCommand::HOLD }, Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::InputType::CHAR, 'c' },
        //
    };

    inline const App::Rules::Rules& TetrisGameRules {
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

    inline const Core::Help::HelpData& TetrisGameHelpCmds {
        {
            { "Left",    { "h", "←" } },
            { "Right",   { "l", "→" } },
            { "Down",    { "j", "↓" } },
            { "Rotate",  { "k", "↑" } },
            { "Drop",    { "space" } },
            { "Restart", { "r" } },
            { "Pause",   { "p" } },
            { "Quit",    { "q" } },
        }
    };

	class TetrisGame : public IGame
	{
	public:
        TetrisGame(size_t width = 24, size_t height = 20)
        : IGame{ { width, height } }
        , m_board{ width, height }
        {}

        void init() override;
        void update() override;
        void reset() override;
		bool isGameOver() const override;

        bool handleEvent(Core::CommandVariant e) override;
        void collectRenderData(Core::RenderQueue& out) const override;

        const App::Rules::Rules& getRules() const override { return TetrisGameRules; }
        const Core::Help::HelpData& getHelpData() const override { return TetrisGameHelpCmds; }
        const std::vector<Core::InputBinding>& getBindings() const override { return TetrisGameRegisteredEvents; }

    private:
        TetrisBoard m_board;
        Core::Container::Deck<Tetromino> m_deck;
	};

}