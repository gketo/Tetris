#pragma once

#include "Core/Event/CommandVariant.h"
#include "Core/Event/Binding/DeviceType.h"
#include "Core/Event/Binding/InputBinding.h"
#include "Core/Event/Binding/InputType.h"
#include "Core/Event/Binding/SourceType.h"

#include <vector>

namespace Core {

    const std::vector<InputBinding> GameChoiceMenuRegisteredEvents
    {
        /*  Keyboard    */
        //  Game choice menu
        InputBinding{ Core::EventLayer::Menu, CommandVariant{ std::in_place_type<MenuCommand>, MenuCommand::MENU_MOVE_UP }, SourceType::TERMINAL, DeviceType::KEYBOARD, InputType::ARROW_UP },
        InputBinding{ Core::EventLayer::Menu, CommandVariant{ std::in_place_type<MenuCommand>, MenuCommand::MENU_MOVE_DOWN }, SourceType::TERMINAL, DeviceType::KEYBOARD, InputType::ARROW_DOWN },
        InputBinding{ Core::EventLayer::Menu, CommandVariant{ std::in_place_type<MenuCommand>, MenuCommand::MENU_SELECT }, SourceType::TERMINAL, DeviceType::KEYBOARD, InputType::ENTER },
        InputBinding{ Core::EventLayer::Menu, CommandVariant{ std::in_place_type<MenuCommand>, MenuCommand::MENU_CANCEL }, SourceType::TERMINAL, DeviceType::KEYBOARD, InputType::CHAR, 'q' },
        //
    };

    const std::vector<InputBinding> GameStatePlayingRegisteredEvents
    {
        /*  Keyboard    */
        //  Pause key
        InputBinding{ Core::EventLayer::EngineRunning, CommandVariant{ std::in_place_type<EngineCommand>, EngineCommand::PAUSE }, SourceType::TERMINAL, DeviceType::KEYBOARD, InputType::CHAR, 'p' },
        //
    };

    const std::vector<InputBinding> GameStatePausedRegisteredEvents
    {
        /*  Keyboard    */
        //  Paused menu options
        InputBinding{ Core::EventLayer::GameMenu, CommandVariant{ std::in_place_type<MenuCommand>, MenuCommand::MENU_MOVE_UP }, SourceType::TERMINAL, DeviceType::KEYBOARD, InputType::ARROW_UP },
        InputBinding{ Core::EventLayer::GameMenu, CommandVariant{ std::in_place_type<MenuCommand>, MenuCommand::MENU_MOVE_DOWN }, SourceType::TERMINAL, DeviceType::KEYBOARD, InputType::ARROW_DOWN },
        InputBinding{ Core::EventLayer::GameMenu, CommandVariant{ std::in_place_type<MenuCommand>, MenuCommand::MENU_SELECT }, SourceType::TERMINAL, DeviceType::KEYBOARD, InputType::ENTER },
        //  Paused menu quit
        InputBinding{ Core::EventLayer::GameMenu, CommandVariant{ std::in_place_type<EngineCommand>, EngineCommand::QUIT }, SourceType::TERMINAL, DeviceType::KEYBOARD, InputType::CHAR, 'q' },
        //
    };

    const std::vector<InputBinding> GameStatePausedRulesRegisteredEvents
    {
        /*  Keyboard    */
        //  Accept rules button
        InputBinding{ Core::EventLayer::GameMenu, CommandVariant{ std::in_place_type<MenuCommand>, MenuCommand::MENU_ACCEPT }, SourceType::TERMINAL, DeviceType::KEYBOARD, InputType::ENTER },
        //
    };
}