#pragma once

#include "Cell.h"
#include "Frame2D.h"
#include "TermiosUtils.h"
#include "GraphicsUtils.h"

#include <algorithm>
#include <optional>
#include <string>
#include <type_traits>

namespace Core::Terminal::Termios {

    namespace GfxUtils = Core::Graphics::Utils;
    namespace TermiosUtils = Core::Terminal::Termios;

    using Core::Grid2D::Cell;

    struct TermiosFrame2DRenderHelper
    {
    public:
        // returns frame as terminal printable string
        template<typename TCell>
        static std::string to_string(const ITerminalCore& terminal, const Core::Grid2D::Frame2D<TCell>& frame);

    private:
        template<typename TCell>
        static GfxUtils::Style computeCellStyleDiff(const Cell<TCell>& current, const Cell<TCell>& previous);

    };

    template<typename TCell>
    std::string TermiosFrame2DRenderHelper::to_string(const ITerminalCore& terminal, const Core::Grid2D::Frame2D<TCell>& frame)
    {
        // Ensure the cell content is printable (char for terminal)
        static_assert(std::is_same_v<decltype(frame.getCell(0,0).content), char>, "Frame2D Render: to_string only works with Cell<stringable>");

        std::string frameStr{};

        auto grid = frame.getGrid();
        if (grid.empty())
        {
            return frameStr;
        }

        terminal.hideCursor(frameStr);
        terminal.cursorHome(frameStr);

         // get windows size 
        auto termConfig = terminal.getTerminalConfig();
        auto winHeight = termConfig.height;
        auto winWidth = termConfig.width;

        Cell<char> prevCell{};
        prevCell.setFg(GfxUtils::Color::Invalid);
        prevCell.setBg(GfxUtils::Color::Invalid);

        // for each line in window
        for (int row = 0; row < winHeight; row++)
        {
            terminal.moveCursor(frameStr, row, 0);
            if (row < grid.size())
            {
                const auto& rrow = grid[row];
                
                std::string rowStr{};
                rowStr += TermiosUtils::ERASE_LINE_TORIGHT;
                rowStr += TermiosUtils::RESET_COLORS;
                
                for (size_t col = 0; col < rrow.size(); col++)
                {
                    const auto& currCell = rrow[col];

                    const auto& styleDiff = computeCellStyleDiff(currCell, prevCell);

                    rowStr += TermiosUtils::Termios_toAnsiFgColor(styleDiff.fg);
                    rowStr += TermiosUtils::Termios_toAnsiBgColor(styleDiff.bg);
                    for (const auto& attr : styleDiff.attrs)
                    {
                        rowStr += TermiosUtils::Termios_toAnsiTextAttr(attr);
                    }
                    
                    rowStr.push_back(currCell.content);

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
        terminal.cursorHome(frameStr);

        return frameStr;
    }

    template<typename TCell>
    GfxUtils::Style TermiosFrame2DRenderHelper::computeCellStyleDiff(const Cell<TCell>& current, const Cell<TCell>& previous)
    {
        // style different escape sequences
        GfxUtils::Style styleDiff{};

        // foreground
        styleDiff.fg = current.fg();
        // background
        styleDiff.bg = current.bg();
        
        // typographic attributs
        const auto& currAttr = current.attrs();
        const auto& prevAttr = previous.attrs();

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