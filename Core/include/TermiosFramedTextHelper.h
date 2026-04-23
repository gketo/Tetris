#pragma once

#include "GraphicsUtils.h"
#include "ITerminalCore.h"
#include "Logger.h"
#include "TermiosUtils.h"

#include <algorithm>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>

namespace Core::Terminal::Termios {

    namespace GfxUtils = Core::Graphics::Utils;
    namespace TermiosUtils = Core::Terminal::Termios;

    struct TermiosFramedTextHelper
    {
    public:
        // returns frame as terminal printable string
        static std::string to_string(const Core::ITerminalCore& terminal, const std::vector<std::string_view>& dataVect);
    };

    std::string TermiosFramedTextHelper::to_string(const Core::ITerminalCore& terminal, const std::vector<std::string_view>& dataVect)
    {
        constexpr const char row_border_cell{ '*' };
        constexpr const size_t row_border_height{ 1 };
        constexpr const size_t row_border_outter_padding_width{ 1 };
        constexpr const size_t row_border_inner_padding_width{ 1 };

        constexpr const char col_border_cell{ '*' };
        constexpr const size_t col_border_width{ 1 };
        constexpr const size_t col_border_outter_padding_width{ 1 };
        constexpr const size_t col_border_inner_padding_width{ 1 };

        //
        std::string frameStr{};

        terminal.cursorHome(frameStr);

        // get windows size 
        auto termConfig = terminal.getTerminalConfig();
        auto winHeight = termConfig.height;
        auto winWidth = termConfig.width;

        auto dataVect_count = dataVect.size();
        auto max_data_width = winWidth - 2 * (col_border_outter_padding_width + col_border_width + col_border_inner_padding_width);

        // for each line in window
        for (int row = 0; row < winHeight; )
        {
            // we are centring the data display, creating a border before and around, with inner and outter padding (padding is empty row)
            if (row == (winHeight - dataVect_count)/2 - row_border_outter_padding_width - row_border_height - row_border_inner_padding_width) 
            {
                // top border outter empty padding
                for (int i = 0; i < row_border_outter_padding_width; i++)
                {
                    terminal.moveCursor(frameStr, row, 0);
                    // clear line
                    frameStr += TermiosUtils::ERASE_LINE_TORIGHT;

                    ++row;
                }

                // top border
                for (int i = 0; i < row_border_height; i++)
                {
                    terminal.moveCursor(frameStr, row, 0);
                    // clear line
                    frameStr += ERASE_LINE_TORIGHT;
                    // move after col padding
                    terminal.moveCursor(frameStr, row, col_border_outter_padding_width);
                    // print border
                    frameStr += std::string(winWidth - 2 * col_border_outter_padding_width, row_border_cell);

                    ++row;
                }

                // top border inner empty padding
                for (int i = 0; i < row_border_inner_padding_width; i++)
                {
                    terminal.moveCursor(frameStr, row, 0);
                    // clear line
                    frameStr += ERASE_LINE_TORIGHT;
                    // move after col padding
                    terminal.moveCursor(frameStr, row, col_border_outter_padding_width);
                    // print border
                    frameStr += std::string(col_border_width, col_border_cell);
                    // move to next border
                    terminal.moveCursor(frameStr, row, winWidth - col_border_outter_padding_width - col_border_width);
                    // print border
                    frameStr += std::string(col_border_width, col_border_cell);

                    ++row;
                }

                // dataVect
                std::vector<std::string> dataVectWrapped;
                // if data is too long we wrap it vertically
                for (const auto& data : dataVect)
                {
                    auto wrapped = TermiosUtils::wrap(data, max_data_width);
                    dataVectWrapped.insert(dataVectWrapped.end(), wrapped.begin(), wrapped.end());
                }
                for (const auto& data : dataVectWrapped)
                {
                    
                    terminal.moveCursor(frameStr, row, 0);
                    // clear line
                    frameStr += ERASE_LINE_TORIGHT;
                    // move after col padding
                    terminal.moveCursor(frameStr, row, col_border_outter_padding_width);
                    // print border
                    frameStr += std::string(col_border_width, col_border_cell);
                    // move after inner padding padding
                    terminal.moveCursor(frameStr, row, col_border_outter_padding_width + col_border_width + col_border_inner_padding_width);

                    //todo, implement scrolling (only during dataVect)
                    // move cursor to center data 
                    terminal.moveCursor(frameStr, row, (winWidth - data.size()) / 2);
                    // print data
                    frameStr += data;
                    // move to next border
                    terminal.moveCursor(frameStr, row, winWidth - col_border_outter_padding_width - col_border_width);
                    // print border
                    frameStr += std::string(col_border_width, col_border_cell);
    
                    ++row;
                }

                // bottom border inner empty padding
                for (int i = 0; i < row_border_inner_padding_width; i++)
                {
                    terminal.moveCursor(frameStr, row, 0);
                    // clear line
                    frameStr += ERASE_LINE_TORIGHT;
                    // move after col padding
                    terminal.moveCursor(frameStr, row, col_border_outter_padding_width);
                    // print border
                    frameStr += std::string(col_border_width, col_border_cell);
                    // move to next border
                    terminal.moveCursor(frameStr, row, winWidth - col_border_outter_padding_width - col_border_width);
                    // print border
                    frameStr += std::string(col_border_width, col_border_cell);

                    ++row;
                }

                // bottom border
                for (int i = 0; i < row_border_height; i++)
                {
                    terminal.moveCursor(frameStr, row, 0);
                    // clear line
                    frameStr += ERASE_LINE_TORIGHT;
                    // move after col padding
                    terminal.moveCursor(frameStr, row, col_border_outter_padding_width);
                    // print border
                    frameStr += std::string(winWidth - 2 * col_border_outter_padding_width, row_border_cell);

                    ++row;
                }

                // bottom border outter empty padding
                for (int i = 0; i < row_border_outter_padding_width; i++)
                {
                    terminal.moveCursor(frameStr, row, 0);
                    // clear line
                    frameStr += TermiosUtils::ERASE_LINE_TORIGHT;

                    ++row;
                }
            }
            else
            {
                terminal.moveCursor(frameStr, row, 0);
                frameStr += TermiosUtils::ERASE_LINE_TORIGHT;
                row++;
            }
        }

        frameStr += TermiosUtils::RESET_ATTRS;
        frameStr += TermiosUtils::RESET_COLORS;
        terminal.cursorHome(frameStr);

        return frameStr;
    }

}

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