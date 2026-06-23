#pragma once

#include <string_view>

namespace Core {

    enum class MenuCommand
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

    // Helper function to convert MenuCommand to string
    inline std::string_view dbg_to_string(MenuCommand action)
    {
        switch (action)
        {
        case MenuCommand::MENU_ACCEPT:      return "ACCEPT";
        case MenuCommand::MENU_CANCEL:      return "MENU_CANCEL";
        case MenuCommand::MENU_MOVE_UP:     return "MENU_MOVE_UP";
        case MenuCommand::MENU_MOVE_DOWN:   return "MENU_MOVE_DOWN";
        case MenuCommand::MENU_SELECT:      return "MENU_SELECT";
        }
        return "Unknown";
    }

}