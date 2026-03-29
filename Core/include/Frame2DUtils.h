#pragma once

#include "Cell.h"
#include "Frame2D.h"
#include "TerminalUtils.h"

#include <string>

namespace Core {

    class Frame2DUtils
    {
    public:
        // returns frame as terminal printable string
        static std::string to_string(const Frame2D& frame)
        {
            auto grid = frame.getGrid();

            if (grid.empty())
            {
                return "";
            }

            std::string buf{};
            //buf.reserve(cells2d.size() * cells2d[0].size() * 8);


            Cell prevCell{};
            prevCell.fg = Color::Unvalid;
            prevCell.bg = Color::Unvalid;

            for (const auto& row : grid)
            {
                for (size_t i = 0; i < row.size(); ++i)
                {
                    const auto& currCell = row[i];

                    buf.append(computeStyleDiff(currCell, prevCell));
                    buf.push_back(currCell.ch);

                    prevCell = currCell;

                    // end of line
                    if (i == row.size() - 1)
                    {
                        buf.append("\033[39m\033[49m");      // reset colors
                        buf.push_back('\n');

                        prevCell.fg = Color::Fg_Default;
                        prevCell.bg = Color::Bg_Default;

                        //prevCell.attr.clear();
                        //prevCell.attr.pussh_back(Attr::Default);
                    }
                }
                
            }

            return buf;
        }
    
        static const Frame2D& dbg_createComprehensiveTestFrame(size_t rows, size_t cols) 
        {
            static Frame2D frame{ rows, cols };         // static cause ensure lifetime, for debug dbg only

            // Step 1: Allocate a 5x5 frame
            frame.resize(rows, cols);

            // Step 2: Fill with some initial pattern
            for (size_t r = 0; r < rows; ++r) 
            {
                for (size_t c = 0; c < cols; ++c) 
                {
                    Cell cell;
                    cell.ch = '0' + (r + c) % 10;         // character pattern
                    cell.fg = static_cast<Color>(r % 8);  // foreground varies by row
                    cell.bg = static_cast<Color>(c % 8);  // background varies by col
                    if ((r + c) % 2 == 0) cell.addAttr(Attr::BOLD);
                    frame.setCell(r, c, cell);
                }
            }

            // Step 3: Append a row
            std::vector<Cell> newRow(cols);
            for (size_t c = 0; c < cols; ++c) 
            {
                newRow[c].ch = 'a' + c;
                newRow[c].fg = Color::Fg_Default;
                newRow[c].bg = Color::Bg_Default;
                newRow[c].addAttr(Attr::UNDERLINED);
            }
            frame.appendRow(newRow);

            // Step 4: Append a column
            Cell colCell;
            colCell.ch = '*';
            colCell.fg = Color::Fg_Default;
            colCell.bg = Color::Bg_Default;
            colCell.addAttr(Attr::ITALICS);
            frame.appendColumn(colCell);

            // Step 5: Clear a third of the frame with a special cell
            Cell emptyCell;
            emptyCell.ch = '.';
            emptyCell.fg = Color::Fg_Default;
            emptyCell.bg = Color::Bg_Default;
            for (size_t r = 0; r < rows/3; ++r) 
            {
                for (size_t c = 0; c < cols/3; ++c) 
                {
                    frame.setCell(r, c, emptyCell);
                }
            }

            // Step 6: Return the frame ready for rendering
            return frame;
        }

    private:
        static std::string computeStyleDiff(const Cell& current, const Cell& previous)
        {
            // style different escape sequences
            std::string stylediffstr{};

            // foreground
            if (previous.fg != current.fg)
            {
                stylediffstr.append(Termios_toAnsiFg(current.fg));
            }
            // background
            if (previous.bg != current.bg)
            {
                stylediffstr.append(Termios_toAnsiBg(current.bg));
            }
            
            // typographic attributs
            const auto& currAttr = current.attrs();
            const auto& prevAttr = previous.attrs();

            // compute difference: elements in currAttr  but not in prevAttr
            // if prev empty all curr taken, if curr empty no attr taken
            std::vector<Attr> attrDiff;
            std::set_difference(currAttr.begin(), currAttr.end(),
                                prevAttr.begin(), prevAttr.end(),
                                std::back_inserter(attrDiff));

            for (const auto& attr : attrDiff) 
            {
                stylediffstr.append(Termios_toAnsiAttr(attr));
            }
            
            return stylediffstr;
        }
    };
} // namespace Core
