#pragma once

#include "CommandVariant.h"
#include "DeviceEvent.h"
#include "DeviceType.h"
#include "InputBinding.h"
#include "KeyCode.h"
#include "SourceType.h"
#include "TetrisCommand.h"

namespace App {

    // const std::vector<Core::InputBinding> TetrisGameRegisteredEvents{
    //     // Keyboard
    //     Core::InputBinding{ Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::MOVE_LEFT }, Core::DeviceEvent{ Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::ARROW_LEFT } },
    //     Core::InputBinding{ Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::MOVE_RIGHT }, Core::DeviceEvent{ Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::ARROW_RIGHT } },
    //     Core::InputBinding{ Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::SOFT_DROP }, Core::DeviceEvent{ Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::ARROW_DOWN } },
    //     Core::InputBinding{ Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::ROTATE_CLOCKWISE }, Core::DeviceEvent{ Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::ARROW_UP } },
    //     Core::InputBinding{ Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::ROTATE_LEFT }, Core::DeviceEvent{ Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::CHAR, 'z' } },
    //     Core::InputBinding{ Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::ROTATE_RIGHT }, Core::DeviceEvent{ Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::CHAR, 'x' } },
    //     Core::InputBinding{ Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::HARD_DROP }, Core::DeviceEvent{ Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::SPACEBAR } },
    //     Core::InputBinding{ Core::CommandVariant{ std::in_place_type<Game::Tetris::TetrisCommand>, Game::Tetris::TetrisCommand::HOLD }, Core::DeviceEvent{ Core::SourceType::TERMINAL, Core::DeviceType::KEYBOARD, Core::KeyCode::CHAR, 'c' } },
    //     //
    // };

} 

    // DeviceEvent(SourceType source, DeviceType device, KeyCode code, std::optional<char> ch = std::nullopt, KeyModifier modifiers = KeyModifier::None)
