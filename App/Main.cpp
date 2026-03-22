// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "CtrlKeyboard.h"
#include "EventManager.h"
#include "Game.h"
#include "GameEngine.h"
#include "TerminalLib.h"

#include <iostream>
#include <string>
#include <windows.h>

int main()
{
    std::cout << "Hello World!\n";

    Core::GameMaster gm{};

    Core::TerminalLib terminal{ STD_INPUT_HANDLE };
    terminal.enableRawMode();

    Core::CtrlKeyboard controller{Core::DeviceType::keyboard, terminal};

    Core::EventManager<Game::Action> em{ controller };

    Core::GameEngine<Game::Action> ge{ gm, em };

    if (ge.init())
        ge.run();

}
