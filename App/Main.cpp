// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "CtrlKeyboard.h"
#include "EventManager.h"
#include "Game.h"
#include "GameEngine.h"
#include "ITerminalCore.h"
#include "Logger.h"

/* DEBUG */
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void crashHandler(int sig) {
    void *array[20];
    size_t size = backtrace(array, 20);
    fprintf(stderr, "Signal %d received (likely pure virtual call)\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    _exit(1);
}

int main()
{
    // DEBUG
    //signal(SIGABRT, crashHandler); // catches abort caused by pure virtual call

    LOG_DEBUG("[Main.cpp] Hello World!");

    Core::GameMaster gm{};

    auto terminal {Core::createTerminalCore()};
    if (terminal)
    {
        terminal->init();
    }

    Core::CtrlKeyboard controller{*terminal};

    Core::EventManager em{ controller };

    Core::GameEngine ge{ gm, em , *terminal};

    try 
    {
        ge.init();
    } 
    catch (...)
    {
        LOG_DEBUG("[Main.cpp] Can't initialize GameEngine");
    }

    try 
    {
        ge.run();
    } 
    catch (...)
    {
        LOG_DEBUG("[Main.cpp] Can't run GameEngine");
    }


    return 0;
}