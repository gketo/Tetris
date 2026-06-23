#pragma once

#include "Core/Terminal/TerminalBuffer.h"
#include "Core/Terminal/TerminalConfig.h"
#include "App/Game/Tetris/TetrisBoard.h"

#include <stdexcept>

namespace Core::Terminal::Termios {

    void buildBuffer(Core::Terminal::TerminalBuffer& buffer, const Core::Terminal::TerminalConfig& tConfig, const App::Game::Tetris::TetrisBoard& tetrisBoard)
    {
        if (tetrisBoard.empty())
        {
            return;
        }

        if (tConfig.size.width < tetrisBoard.size().rows || tConfig.size.height < tetrisBoard.size().cols)
        {
            throw std::runtime_error("[RenderTetrisTermios] buildBuffer() Terminal is too small. Can't render Tetris.");
        }

        auto boardData = tetrisBoard.data();
        for (size_t r = 0; r < tConfig.size.height; ++r)
        {
            
        }


    }
}