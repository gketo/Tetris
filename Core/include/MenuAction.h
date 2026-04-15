#pragma once

#include <string_view>

namespace Core {

    enum class MenuAction
    {
        //
        MENU_ACCEPT,
        MENU_CANCEL,
        // Menu selection
        MENU_MOVE_UP,
        MENU_MOVE_DOWN,
        MENU_SELECT,
       //
    };

    // Helper function to convert MenuAction enum to string
    inline std::string_view menuaction_to_string(MenuAction action)
    {
        switch (action)
        {
        case MenuAction::MENU_ACCEPT: return "ACCEPT";
        case MenuAction::MENU_CANCEL: return "MENU_CANCEL";
        case MenuAction::MENU_MOVE_UP: return "MENU_MOVE_UP";
        case MenuAction::MENU_MOVE_DOWN: return "MENU_MOVE_DOWN";
        case MenuAction::MENU_SELECT: return "MENU_SELECT";
        }
    }

}