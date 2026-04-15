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

    struct TermiosFrameRenderHelper
    {
    public:
        // returns frame as terminal printable string
        template<typename TCell>
        static std::string to_string(const Core::Grid2D::Frame2D<TCell>& frame);

    private:
        template<typename TCell>
        static GfxUtils::Style computeCellStyleDiff(const Cell<TCell>& current, const Cell<TCell>& previous);

    };

    template<typename TCell>
    std::string TermiosFrameRenderHelper::to_string(const Core::Grid2D::Frame2D<TCell>& frame)
    {
        // Ensure the cell content is printable (char for terminal)
        static_assert(std::is_same_v<decltype(frame.getCell(0,0).content), char>, "Frame2D Render: to_string only works with Cell<stringable>");

        std::string frameStr{};

        auto grid = frame.getGrid();
        if (grid.empty())
        {
            return frameStr;
        }

        Cell<char> prevCell{};
        prevCell.setFg(GfxUtils::Color::Invalid);
        prevCell.setBg(GfxUtils::Color::Invalid);

        frameStr += CURSOR_HOME.data();

        for (const auto& row : grid)
        {
            std::string rowStr{};
            rowStr += ERASE_RIGHT.data();
            rowStr += TermiosUtils::RESET_COLORS.data();
            
            for (size_t col = 0; col < row.size(); ++col)
            {
                const auto& currCell = row[col];

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
                if (col == row.size() - 1)
                {
                    rowStr.append(TermiosUtils::RESET_COLORS.data());      // reset colors
                    rowStr.push_back('\r');
                    rowStr.push_back('\n');

                    prevCell.setFg(GfxUtils::Color::Invalid);
                    prevCell.setBg(GfxUtils::Color::Invalid);

                }
            }
            frameStr += rowStr;
        }

        // frameStr += CURSOR_HOME.data();

        return frameStr;
    }

    template<typename TCell>
    GfxUtils::Style TermiosFrameRenderHelper::computeCellStyleDiff(const Cell<TCell>& current, const Cell<TCell>& previous)
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