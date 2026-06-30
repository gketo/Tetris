#pragma once

// ==================== Includes ====================
#include "Core/Containers/Board/Board.h"
#include "Core/Containers/Board/Cell.h"
#include "Core/Containers/Board/CellVisual.h"

#include "Core/Geometry/Rect.h"

#include "Core/Graphics/GfxUtils.h"

#include "Core/Render/BoardView.h"
#include "Core/Render/Surface.h"

#include "Core/Terminal/TerminalSurface.h"
#include "Core/Terminal/TerminalUtils.h"
#include "Core/Terminal/Termios/TermiosUtils.h"

#include "Core/Utils/Logger.h"

// ==================== Includes ====================
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