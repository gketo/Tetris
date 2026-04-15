
#pragma once

#include "Cell.h"
#include "Frame2D.h"
#include "GraphicsUtils.h"

namespace Core::Debug {

    namespace GfxUtils = Core::Graphics::Utils;

    template<typename TCell>
    static const Core::Grid2D::Frame2D<TCell> dbg_createEmptyFrame(size_t rows, size_t cols)
    {
        static Core::Grid2D::Frame2D<TCell> frame{ rows, cols };
        return frame;
    }

    template<typename TCell>
    static const Core::Grid2D::Frame2D<TCell> dbg_createComprehensiveTestFrame(size_t rows, size_t cols) 
    {
        // Static frame for debug lifetime
        static Core::Grid2D::Frame2D<TCell> frame{ rows, cols };
        frame.resize(rows, cols);

        // Valid foreground/background colors
        constexpr GfxUtils::Color validFgColors[] = {
            GfxUtils::Color::BLACK,
            GfxUtils::Color::RED,
            GfxUtils::Color::GREEN,
            GfxUtils::Color::YELLOW,
            GfxUtils::Color::BLUE,
            GfxUtils::Color::MAGENTA,
            GfxUtils::Color::CYAN,
            GfxUtils::Color::WHITE
        };

        constexpr GfxUtils::Color validBgColors[] = {
            GfxUtils::Color::BLACK,
            GfxUtils::Color::RED,
            GfxUtils::Color::GREEN,
            GfxUtils::Color::YELLOW,
            GfxUtils::Color::BLUE,
            GfxUtils::Color::MAGENTA,
            GfxUtils::Color::CYAN,
            GfxUtils::Color::WHITE
        };

        // Fill main frame
        for (size_t r = 0; r < rows; ++r) 
        {
            for (size_t c = 0; c < cols; ++c) 
            {
                Core::Grid2D::Cell<TCell> cell;
                cell.content = '0' + (r + c) % 10;

                // Mostly valid colors
                cell.setFg(validFgColors[r % 8]);
                cell.setBg(validBgColors[c % 8]);

                // Bold on even positions
                if ((r + c) % 2 == 0)
                    cell.addAttr(GfxUtils::Attr::BOLD);

                frame.setCell(r, c, cell);
            }
        }

        // Append a row with UNDERLINED and default colors
        std::vector<Core::Grid2D::Cell<TCell>> newRow(cols);
        for (size_t c = 0; c < cols; ++c) 
        {
            newRow[c].content = ('a' + c % 26);
            newRow[c].setFg(GfxUtils::Color::Fg_Default);
            newRow[c].setBg(GfxUtils::Color::Bg_Default);
            newRow[c].addAttr(GfxUtils::Attr::UNDERLINED);
        }
        frame.appendRow(newRow);

        // Append a column with ITALICS and default colors
        Core::Grid2D::Cell<TCell> colCell;
        colCell.content = '*';
        colCell.setFg(GfxUtils::Color::Fg_Default);
        colCell.setBg(GfxUtils::Color::Bg_Default);
        colCell.addAttr(GfxUtils::Attr::ITALICS);
        frame.appendColumn(colCell);

        // Clear top-left third with '.' using default colors
        Core::Grid2D::Cell<TCell> emptyCell;
        emptyCell.content = '.';
        emptyCell.setFg(GfxUtils::Color::Fg_Default);
        emptyCell.setBg(GfxUtils::Color::Bg_Default);

        for (size_t r = 0; r < rows / 3; ++r) 
        {
            for (size_t c = 0; c < cols / 3; ++c) 
            {
                frame.setCell(r, c, emptyCell);
            }
        }

        return frame;
    }

}