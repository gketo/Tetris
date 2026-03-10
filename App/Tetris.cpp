// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "CtrlKeyboard.h"
#include "EventManager.h"
#include "GameEngine.h"
#include "TerminalLib.h"

#include <iostream>
#include <string>
#include <windows.h>

namespace TetrisGame
{
    enum class UserActions
    {
        PLAY,
        PAUSE,
        ROTATE_LEFT,
        ROTATE_RIGHT,
        QUIT,
        MAX_USER_ACTIONS
    };
};

using UserActions = TetrisGame::UserActions;

int main()
{
    std::cout << "Hello World!\n";

    Core::GameMaster gm{};

    Core::CtrlKeyboard ci{Core::DeviceType::keyboard};
    Core::EventManager<UserActions> em{};

    Core::GameEngine<UserActions> ge{ gm, em, ci };

    ge.init();
    ge.run();

    Core::TerminalLib ti{ STD_INPUT_HANDLE };
    ti.enableRawMode();
    ti.read(true);

}
