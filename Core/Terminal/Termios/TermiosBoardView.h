#pragma once

#include "Core/Containers/Board/Board.h"
#include "Core/Render/BoardView.h"
#include "Core/Containers/Board/CellVisual.h"
#include "Core/Containers/Board/Cell.h"
#include "Core/Graphics/GfxUtils.h"
#include "Core/Geometry/Rect.h"
#include "Core/Render/Surface.h"
#include "Core/Terminal/TerminalSurface.h"
#include "Core/Terminal/Termios/TermiosUtils.h"
#include "Core/Terminal/TerminalUtils.h"

#include "Core/Utils/Logger.h"

#include <stdexcept>
#include <string>
#include <variant>

namespace Core::Terminal::Termios {

    namespace GfxUtils = Core::Graphics::Utils;
    namespace TermiosUtils = Core::Terminal::Termios::Utils;
    namespace TerminalUtils = Core::Terminal::Utils;

    struct TermiosBoardView : public Core::Render::BoardView
    {
        void renderToSurface(const Core::Container::Board& board, Core::Render::Surface& surface, const Core::Geometry::Rect& rect) const override;
    };

    void TermiosBoardView::renderToSurface(const Core::Container::Board& board, Core::Render::Surface& surface, const Core::Geometry::Rect& rect) const
    {
        auto* termSurface = dynamic_cast<Core::Terminal::TerminalSurface*>(&surface);

        if (!termSurface)
        {
            throw std::runtime_error("[TermiosBoardView] renderToSurface() Invalid surface type");
        }

        if (termSurface->data.empty())
        {
            throw std::runtime_error("[TermiosBoardView] renderToSurface() must provide allocated surface");
        }

        if (board.empty())
        {
            return;
        }

        auto startRow = rect.start.y;
        auto startCol = rect.start.x;
        auto maxRow = startRow + rect.size.height;
        auto maxCol = startCol + rect.size.width;

        auto boardData = board.data();

        // for each row in rect
        for (size_t shapeRow = startRow; shapeRow < maxRow; ++shapeRow)
        {
            for (size_t shapeCol = startCol; shapeCol < maxCol; ++shapeCol)
            {
                auto dataRow = shapeRow - startRow;
                auto dataCol = shapeCol - startCol;

                if (dataRow < board.size().rows && dataCol < board.size().cols)
                {
                    const auto& cell = boardData(shapeRow, shapeCol);//.at(shapeRow, shapeCol);

                    std::string cellStr;

                    // move to row and col
                    if (shapeCol == startCol)
                    {
                        TermiosUtils::appendMoveCursor(cellStr, shapeRow, shapeCol);
                    }

                    termSurface->data.at(dataRow, dataCol) = TerminalUtils::Terminal_CellVisualToTerminalChar(cell.visual);
                }
            }                
        }
    }
}

 // for (const auto& elem : cell.visual.elements)
                    // {
                    //     std::visit([&cellStr, &prevStyle](const auto& e) {
                    //         using T = std::decay_t<decltype(e)>;

                    //         if constexpr (std::is_same_v<T, Core::Container::BlockElement>)
                    //         {
                    //             // LOG_DEBUG("block elem %s", dbg_to_string(e.blockColor));
                    //             cellStr += TermiosUtils::Termios_FgColorToAnsi(e.blockColor);
                    //             cellStr += TermiosUtils::Termios_BgColorToAnsi(e.blockColor);
                    //             cellStr += ' ';
                    //             cellStr += TermiosUtils::RESET_COLORS;      // reset colors
                    //         }
                    //         else if constexpr (std::is_same_v<T, Core::Container::BorderElement>)
                    //         {
                    //             return;
                    //         }
                    //         else if constexpr (std::is_same_v<T, Core::Container::GlyphElement>)
                    //         {
                    //             auto styleDiff = e.style.computeStyleDiff(prevStyle);

                    //             cellStr += TermiosUtils::Termios_FgColorToAnsi(styleDiff.fg);
                    //             cellStr += TermiosUtils::Termios_BgColorToAnsi(styleDiff.bg);

                    //             for (const auto& attr : styleDiff.attrs)
                    //             {
                    //                 cellStr += TermiosUtils::Termios_TextAttrToAnsi(attr);
                    //             }

                    //             if (e.glyph)
                    //             {
                    //                 cellStr += TerminalUtils::Terminal_UnicodeToUtf8(*(e.glyph));
                    //             }
                    //             else
                    //             {
                    //                 cellStr += ' ';
                    //             }

                    //             prevStyle = e.style;
                    //         }
                    //         else if constexpr (std::is_same_v<T, Core::Container::ImageElement>)
                    //         {
                    //             // LOG_DEBUG("image elem %d", e.imageId);
                    //             return;
                    //         }
                    //         else
                    //         {
                    //             LOG_ERROR("[TermiosBoardView] renderToSurface(): undefined/wrong visual type");
                    //         }
                    //     }, elem);
                    // }

                    // if (shapeCol == maxCol - 1)
                    // {
                    //     // end of line
                    //     cellStr += TermiosUtils::RESET_COLORS;      // reset colors

                    //     prevStyle.fg = GfxUtils::Color::Invalid;
                    //     prevStyle.bg = GfxUtils::Color::Invalid;
                    // }