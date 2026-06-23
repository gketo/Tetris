#pragma once

#include "App/Game/Tetris/TetrominoBlock.h"
#include "Core/Grid2D.h"
#include "Core/Graphics/GfxUtils.h"
#include "Core/Terminal/ITerminalCore.h"
#include "Core/Terminal/Termios/TermiosUtils.h"

#include <cstddef>
#include <optional>
#include <string>
#include <type_traits>
#include <unordered_set>


#ifdef EXCLUDE_THIS
namespace Core::Terminal::Termios {

    namespace GfxUtils = Core::Graphics::Utils;
    namespace TermiosUtils = Core::Terminal::Termios::Utils;

    struct TermiosTetrisRenderHelper
    {
    public:
        // returns frame as terminal printable string
        static std::string toString(const Core::ITerminalCore& terminal, const Grid::Grid2D<App::Game::Tetris::TetrominoBlock>& frame);

    private:
        static GfxUtils::Style computeCellStyleDiff(const App::Game::Tetris::TetrominoBlock& current, const App::Game::Tetris::TetrominoBlock& previous);

    };

    std::string TermiosTetrisRenderHelper::toString(const Core::ITerminalCore& terminal, const Grid::Grid2D<App::Game::Tetris::TetrominoBlock>& frame)
    {
        std::string frameStr{};

        if (frame.empty())
        {
            return frameStr;
        }

        terminal.appendHideCursor(frameStr);
        terminal.appendCursorHome(frameStr);

        // get windows size 
        auto termConfig = terminal.getTerminalConfig();
        auto winHeight = termConfig.size.height;

        App::Game::Tetris::TetrominoBlock prevCell{};
        prevCell.setFg(GfxUtils::Color::Invalid);
        prevCell.setBg(GfxUtils::Color::Invalid);

        // for each wrow in window
        for (size_t wrow = 0; wrow < winHeight; ++wrow)
        {
            terminal.appendMoveCursor(frameStr, wrow, 0);
            if (wrow < frame.rows())
            {
                // data row
                const auto& rrow = frame.row(wrow);
                
                std::string rowStr{};
                rowStr += TermiosUtils::ERASE_LINE_TORIGHT;
                rowStr += TermiosUtils::RESET_COLORS;
                
                for (size_t col = 0; col < rrow.size(); ++col)
                {
                    const auto& currCell = rrow[col];

                    const auto& styleDiff = computeCellStyleDiff(currCell, prevCell);

                    rowStr += TermiosUtils::Termios_FgColorToAnsi(styleDiff.fg);
                    rowStr += TermiosUtils::Termios_BgColorToAnsi(styleDiff.bg);
                    for (const auto& attr : styleDiff.attrs)
                    {
                        rowStr += TermiosUtils::Termios_TextAttrToAnsi(attr);
                    }
                    
                    rowStr.push_back(' ');

                    prevCell = currCell;

                    // end of line
                    if (col == rrow.size() - 1)
                    {
                        rowStr += TermiosUtils::RESET_COLORS;      // reset colors

                        prevCell.setFg(GfxUtils::Color::Invalid);
                        prevCell.setBg(GfxUtils::Color::Invalid);
                    }
                }
                frameStr += rowStr;
            }
            else
            {
                frameStr += TermiosUtils::ERASE_LINE_TORIGHT;
            }
        }
        frameStr += TermiosUtils::RESET_ATTRS;
        frameStr += TermiosUtils::RESET_COLORS;
        terminal.appendCursorHome(frameStr);

        TermiosUtils::frameContent(terminal, frameStr, "Tetris", frame.rows(), frame.cols());

        return frameStr;
    }

    GfxUtils::Style TermiosTetrisRenderHelper::computeCellStyleDiff(const App::Game::Tetris::TetrominoBlock& current, const App::Game::Tetris::TetrominoBlock& previous)
    {
        // style different escape sequences
        GfxUtils::Style styleDiff{};

        // foreground
        styleDiff.fg = current.fg();
        // background
        styleDiff.bg = current.bg();
        
        // typographic attributs
        // compute difference: elements in currAttr  but not in prevAttr
        styleDiff.attrs.clear();
        for (const auto& a : current.attrs())
        {
            if (!previous.hasAttr(a)) {
                styleDiff.attrs.insert(a);
            }
        }

        return styleDiff;
    }

}

#endif
