// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "App/AppLauncher/AppLauncher.h"
#include "Core/Utils/Logger.h"

/* DEBUG */
#include <cstddef>
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
    signal(SIGSEGV, crashHandler);
    signal(SIGABRT, crashHandler);
    signal(SIGILL, crashHandler);
    signal(SIGFPE, crashHandler);

    LOG_DEBUG("[Main.cpp] Hello World!");

    App::Launcher::AppLauncher laucher{};

    try 
    {
        laucher.launch();
    } 
    catch (const std::exception& e) 
    {
        LOG_ERROR("[Main.cpp] Can't launch Launcher: %s", e.what());
    }
    catch (...) 
    {
        LOG_ERROR("[Main.cpp] Can't launch Launcher: unknown exception");
    }

    return 0;
}