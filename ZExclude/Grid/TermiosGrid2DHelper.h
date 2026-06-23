#pragma once

#include "Core/Grid2D.h"
#include "Core/Graphics/GfxUtils.h"
#include "Core/Terminal/ITerminalCore.h"
#include "Core/Terminal/Termios/TermiosUtils.h"
#include "Core/Tile.h"

#include <cstddef>
#include <optional>
#include <string>
#include <type_traits>
#include <unordered_set>

namespace Core::Terminal::Termios {

    namespace GfxUtils = Core::Graphics::Utils;
    namespace TermiosUtils = Core::Terminal::Termios::Utils;

    struct TermiosGrid2DRenderHelper
    {
    public:
        // returns frame as terminal printable string
        template <typename TTile>
        static std::string toString(const Core::Terminal::ITerminalCore& terminal, const App::Grid::Grid2D<TTile>& frame);

    private:
        template <typename TTile>
        static GfxUtils::Style computeTileStyleDiff(const App::Grid::Tile<TTile>& current, const App::Grid::Tile<TTile>& previous);

    };

    template <typename TTile>
    std::string TermiosGrid2DRenderHelper::toString(const Core::Terminal::ITerminalCore& terminal, const App::Grid::Grid2D<TTile>& frame)
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

        App::Grid::Tile<char> prevTile{};
        prevTile.setFg(GfxUtils::Color::Invalid);
        prevTile.setBg(GfxUtils::Color::Invalid);

        // for each winrow in window
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
                    const auto& currTile = rrow[col];

                    const auto& styleDiff = computeTileStyleDiff(currTile, prevTile);

                    rowStr += TermiosUtils::Termios_FgColorToAnsi(styleDiff.fg);
                    rowStr += TermiosUtils::Termios_BgColorToAnsi(styleDiff.bg);
                    for (const auto& attr : styleDiff.attrs)
                    {
                        rowStr += TermiosUtils::Termios_TextAttrToAnsi(attr);
                    }
                    
                    
                    rowStr.push_back(currTile.content ? *currTile.content : ' ');

                    prevTile = currTile;

                    // end of line
                    if (col == rrow.size() - 1)
                    {
                        rowStr += TermiosUtils::RESET_COLORS;      // reset colors

                        prevTile.setFg(GfxUtils::Color::Invalid);
                        prevTile.setBg(GfxUtils::Color::Invalid);
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

        return frameStr;
    }

    template <typename TTile>
    GfxUtils::Style TermiosGrid2DRenderHelper::computeTileStyleDiff(const App::Grid::Tile<TTile>& current, const App::Grid::Tile<TTile>& previous)
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