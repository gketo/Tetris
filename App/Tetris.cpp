// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "GameEngine.h"

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
    
    auto ge = Core::GameEngine();

    ge.run();

}
