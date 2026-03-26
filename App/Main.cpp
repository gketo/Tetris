// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "CtrlKeyboard.h"
#include "EventManager.h"
#include "Game.h"
#include "GameEngine.h"
#include "ITerminalCore.h"
#include "Logger.h"

int main()
{
    LOG_DEBUG("[Main.cpp] Hello World!");

    Core::GameMaster gm{};

    auto terminal {Core::createTerminalCore()};
    if (terminal)
    {
        terminal->init();
    }

    Core::CtrlKeyboard controller{*terminal};

    Core::EventManager em{ controller };

    Core::GameEngine ge{ gm, em };

    ge.init();
    ge.run();

}