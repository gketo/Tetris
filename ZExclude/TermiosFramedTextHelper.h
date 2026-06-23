#pragma once

#include "Core/Graphics/GfxUtils.h"
#include "Core/Terminal/ITerminalCore.h"
#include "Core/Terminal/Termios/TermiosUtils.h"

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

#ifdef EXCLUDE_THIS

namespace Core::Terminal::Termios {

    namespace GfxUtils = Core::Graphics::Utils;
    namespace TermiosUtils = Core::Terminal::Termios::Utils;

    struct TermiosFrameContent
    {
    public:
        // returns frame as terminal printable string
        static void frameContent(const Core::ITerminalCore& terminal, std::string& out, const std::string& title, size_t rows, size_t cols);
    };

}

#endif

            //      char welcome[80];
                
            //     int welcomelen = snprintf(welcome, sizeof(welcome), "Kilo editor -- version %s", KILO_VERSION);
                
            //     if (welcomelen > E.screencols) welcomelen = E.screencols;
                
            //     int padding = (E.screencols - welcomelen) / 2;
                
            //     if (padding)
            //     {
            //         abAppend(ab, "~", 1);
            //         padding--;
            //     }
            //     while (padding--) 
            //         abAppend(ab, " ", 1);
            
            //     abAppend(ab, welcome, welcomelen);
            // }
            
            // } else 
            // {
            //     abAppend(ab, "~", 1);
            // }








             // for each line in window
        // for (int row = 0; row < winHeight; )
        // {
        //     // we are centring the data display, creating a border before and around, with inner and outter padding (padding is empty row)
        //     if (row == (winHeight - dataVect_count)/2 - row_border_outter_padding_width - row_border_height - row_border_inner_padding_width) 
        //     {
        //         // top border outter empty padding
        //         for (int i = 0; i < row_border_outter_padding_width; ++i)
        //         {
        //             terminal.moveCursor(frameStr, row, 0);
        //             // clear line
        //             frameStr += TermiosUtils::ERASE_LINE_TORIGHT;

        //             ++row;
        //         }

        //         // top border
        //         for (int i = 0; i < row_border_height; ++i)
        //         {
        //             terminal.moveCursor(frameStr, row, 0);
        //             // clear line
        //             frameStr += TermiosUtils::ERASE_LINE_TORIGHT;
        //             // move after col padding
        //             terminal.moveCursor(frameStr, row, col_border_outter_padding_width);
        //             // print border
        //             frameStr += std::string(winWidth - 2 * col_border_outter_padding_width, row_border_cell);

        //             ++row;
        //         }

        //         // top border inner empty padding
        //         for (int i = 0; i < row_border_inner_padding_width; ++i)
        //         {
        //             terminal.moveCursor(frameStr, row, 0);
        //             // clear line
        //             frameStr += TermiosUtils::ERASE_LINE_TORIGHT;
        //             // move after col padding
        //             terminal.moveCursor(frameStr, row, col_border_outter_padding_width);
        //             // print border
        //             frameStr += std::string(col_border_width, col_border_cell);
        //             // move to next border
        //             terminal.moveCursor(frameStr, row, winWidth - col_border_outter_padding_width - col_border_width);
        //             // print border
        //             frameStr += std::string(col_border_width, col_border_cell);

        //             ++row;
        //         }

        //         // dataVect
        //         std::vector<std::string> dataVectWrapped;
        //         // if data is too long we wrap it vertically
        //         for (const auto& data : dataVect)
        //         {
        //             auto wrapped = TermiosUtils::wrap(data, max_data_width);
        //             dataVectWrapped.insert(dataVectWrapped.end(), wrapped.begin(), wrapped.end());
        //         }
        //         for (const auto& data : dataVectWrapped)
        //         {
                    
        //             terminal.moveCursor(frameStr, row, 0);
        //             // clear line
        //             frameStr += TermiosUtils::ERASE_LINE_TORIGHT;
        //             // move after col padding
        //             terminal.moveCursor(frameStr, row, col_border_outter_padding_width);
        //             // print border
        //             frameStr += std::string(col_border_width, col_border_cell);
        //             // move after inner padding padding
        //             terminal.moveCursor(frameStr, row, col_border_outter_padding_width + col_border_width + col_border_inner_padding_width);

        //             //todo, implement scrolling (only during dataVect)
        //             // move cursor to center data 
        //             terminal.moveCursor(frameStr, row, (winWidth - data.size()) / 2);
        //             // print data
        //             frameStr += data;
        //             // move to next border
        //             terminal.moveCursor(frameStr, row, winWidth - col_border_outter_padding_width - col_border_width);
        //             // print border
        //             frameStr += std::string(col_border_width, col_border_cell);
    
        //             ++row;
        //         }

        //         // bottom border inner empty padding
        //         for (int i = 0; i < row_border_inner_padding_width; ++i)
        //         {
        //             terminal.moveCursor(frameStr, row, 0);
        //             // clear line
        //             frameStr += TermiosUtils::ERASE_LINE_TORIGHT;
        //             // move after col padding
        //             terminal.moveCursor(frameStr, row, col_border_outter_padding_width);
        //             // print border
        //             frameStr += std::string(col_border_width, col_border_cell);
        //             // move to next border
        //             terminal.moveCursor(frameStr, row, winWidth - col_border_outter_padding_width - col_border_width);
        //             // print border
        //             frameStr += std::string(col_border_width, col_border_cell);

        //             ++row;
        //         }

        //         // bottom border
        //         for (int i = 0; i < row_border_height; ++i)
        //         {
        //             terminal.moveCursor(frameStr, row, 0);
        //             // clear line
        //             frameStr += TermiosUtils::ERASE_LINE_TORIGHT;
        //             // move after col padding
        //             terminal.moveCursor(frameStr, row, col_border_outter_padding_width);
        //             // print border
        //             frameStr += std::string(winWidth - 2 * col_border_outter_padding_width, row_border_cell);

        //             ++row;
        //         }

        //         // bottom border outter empty padding
        //         for (int i = 0; i < row_border_outter_padding_width; ++i)
        //         {
        //             terminal.moveCursor(frameStr, row, 0);
        //             // clear line
        //             frameStr += TermiosUtils::ERASE_LINE_TORIGHT;

        //             ++row;
        //         }
        //     }
        //     else
        //     {
        //         terminal.moveCursor(frameStr, row, 0);
        //         frameStr += TermiosUtils::ERASE_LINE_TORIGHT;
        //         row++;
        //     }
        // }

        // frameStr += TermiosUtils::RESET_ATTRS;
        // frameStr += TermiosUtils::RESET_COLORS;
        // terminal.cursorHome(frameStr);
