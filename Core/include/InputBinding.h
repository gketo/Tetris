#pragma once

#include "DeviceEvent.h"
#include "DeviceType.h"
#include "ActionVariant.h"
#include "KeyCode.h"
#include "SourceType.h"

namespace Core {

    struct InputBinding 
    {
        ActionVariant action;
        DeviceEvent event;
    };

    const std::vector<InputBinding> GameChoiceMenuRegisteredEvents{
        // Keyboard
        //  Game choice menu
        InputBinding{ Core::ActionVariant{ std::in_place_type<MenuAction>, MenuAction::MENU_MOVE_UP }, DeviceEvent{ SourceType::TERMINAL, DeviceType::KEYBOARD, KeyCode::ARROW_UP } },
        InputBinding{ Core::ActionVariant{ std::in_place_type<MenuAction>, MenuAction::MENU_MOVE_DOWN }, DeviceEvent{ SourceType::TERMINAL, DeviceType::KEYBOARD, KeyCode::ARROW_DOWN } },
        InputBinding{ Core::ActionVariant{ std::in_place_type<MenuAction>, MenuAction::MENU_SELECT }, DeviceEvent{ SourceType::TERMINAL, DeviceType::KEYBOARD, KeyCode::ENTER } },
        InputBinding{ Core::ActionVariant{ std::in_place_type<MenuAction>, MenuAction::MENU_CANCEL }, DeviceEvent{ SourceType::TERMINAL, DeviceType::KEYBOARD, KeyCode::CHAR, 'q' } },
        //
    };

    const std::vector<InputBinding> RulesDisplayRegisteredEvents{
        // Keyboard
        //  Accept rules button
        InputBinding{ Core::ActionVariant{ std::in_place_type<MenuAction>, MenuAction::MENU_ACCEPT }, DeviceEvent{ SourceType::TERMINAL, DeviceType::KEYBOARD, KeyCode::ENTER } },
        // InputBinding{ Core::ActionVariant{ std::in_place_type<MenuAction>, MenuAction::MENU_CANCEL }, DeviceEvent{ SourceType::TERMINAL, DeviceType::KEYBOARD, KeyCode::CHAR, 'q'} },
        //
    };

    const std::vector<InputBinding> GameRunningRegisteredEvents{
        // Keyboard
        //  Pause key
        InputBinding{ Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::PAUSE }, DeviceEvent{ SourceType::TERMINAL, DeviceType::KEYBOARD, KeyCode::CHAR, 'p'} },
        //
    };

    const std::vector<InputBinding> GamePausedRegisteredEvents{
        // Keyboard
        //  Paused menu options
        InputBinding{ Core::ActionVariant{ std::in_place_type<MenuAction>, MenuAction::MENU_MOVE_UP }, DeviceEvent{ SourceType::TERMINAL, DeviceType::KEYBOARD, KeyCode::ARROW_UP } },
        InputBinding{ Core::ActionVariant{ std::in_place_type<MenuAction>, MenuAction::MENU_MOVE_DOWN }, DeviceEvent{ SourceType::TERMINAL, DeviceType::KEYBOARD, KeyCode::ARROW_DOWN } },
        InputBinding{ Core::ActionVariant{ std::in_place_type<MenuAction>, MenuAction::MENU_SELECT }, DeviceEvent{ SourceType::TERMINAL, DeviceType::KEYBOARD, KeyCode::ENTER } },
        // Keyboard
        //  Paused menu quit
        InputBinding{ Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::QUIT }, DeviceEvent{ SourceType::TERMINAL, DeviceType::KEYBOARD, KeyCode::CHAR, 'q'} },
        //
    };
} 

    // DeviceEvent(SourceType source, DeviceType device, KeyCode code, std::optional<char> ch = std::nullopt, KeyModifier modifiers = KeyModifier::None)

// em.bindKey( Core::KeyCode::ENTER, Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::SELECT });
// em.bindKey( Core::KeyCode::ENTER, Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::PLAY });
// em.bindKey( Core::KeyCode::KEY_R, Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::RESUME });
// em.bindKey( Core::KeyCode::KEY_P, Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::PAUSE });
// em.bindKey( Core::KeyCode::KEY_Q, Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::QUIT });
// em.bindKey( Core::KeyCode::ARROW_UP, Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::MOVE_UP });
// em.bindKey( Core::KeyCode::ARROW_DOWN, Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::MOVE_DOWN });