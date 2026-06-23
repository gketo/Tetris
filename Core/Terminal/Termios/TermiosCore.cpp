#include "Core/Terminal/Termios/TermiosCore.h"

#include "Core/Event/Events/DeviceEvent.h"
// #include "Core/Grid2D.h"
#include "Core/Event/Binding/InputType.h"
#include "Core/Utils/Logger.h"
#include "Core/Menu/MenuData.h"
#include "Core/Geometry/Rect.h"
#include "Core/Terminal/Termios/TermiosBoardView.h"
#include "Core/Terminal/Termios/TermiosHelpView.h"
#include "Core/Terminal/Termios/TermiosMenuView.h"
// #include "Core/TermiosFramedTextHelper.h"
// #include "Core/TermiosGrid2DHelper.h"
// #include "Core/TermiosTetrisHelper.h"
#include "Core/Terminal/Termios/TermiosUtils.h"
#include "Core/Terminal/TerminalChar.h"

#include "App/Game/Tetris/TetrisBoard.h"
// #include "Core/Tile.h"

#include <iostream>

#include <array>
#include <cstddef>
#include <cstdio>
#include <errno.h>
#include <format>
#include <memory>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <string>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <utility>

#define CTRL_KEY(k) ((k) & 0x1f)

        // output buffer
        // we start here 
        // todo this only renders to rectangle and push to be printed in buffer
        // i need another layer managing which data is collected depending on windows size
        // maybe all data sits in renderqueue and we only render from there the data were interested in 
        //  in that case i need managing when data is skipped do we keep it or not 
        // right now it doesnt work because the clear screen logic etc is off and probably some other stuf 
        // and also because board is constructed with cells that dont have a visual. so i need to add a way to default visual or add visual.
        //  ex empty tetris board cell should be glyph elem with dots
        // right now it smeems with the prints ive put in termiosboardview that no visual elmeents are defined for cells 

namespace Core::Terminal::Termios {

    std::unique_ptr<ITerminalCore> createTerminalCore()
    {
        return std::make_unique<TermiosCore>();
    }

    std::optional<DeviceEvent> TermiosCore::readEvent() const
    {
        char c;
        ssize_t nread;

        nread = read(STDIN_FILENO, &c, 1);

        if (nread == 0)
        {
            return std::nullopt;
        }
        else if (nread == -1)
        {
            if (errno == EAGAIN)
            {
                return std::nullopt; // no input yet, not an error
            }
            else
            {
                throw std::runtime_error("[TermiosCore] readEvent() failed"); // real error
            }
        }

        // caught an event
        DeviceEvent event;

        event.source = SourceType::TERMINAL;
        event.device = DeviceType::KEYBOARD;

        if (c == '\x1b') //escape or escape sequence
        {
            char seq[3];
            if ((nread = read(STDIN_FILENO, &seq[0], 1)) != 1)
            {
                event.input = InputType::ESCAPE;
                return event;
            }
            if ((nread = read(STDIN_FILENO, &seq[1], 1)) != 1)
            {
                event.input = InputType::ESCAPE;
                return event;
            }                

            if (seq[0] == '[') 
            {
                if (seq[1] >= '0' && seq[1] <= '9') 
                {
                    if (read(STDIN_FILENO, &seq[2], 1) != 1)
                    {
                        event.input = InputType::ESCAPE;
                        return event;
                    }
                    if (seq[2] == '~') 
                    {
                        switch (seq[1]) 
                        {
                        case '1': event.input = InputType::HOME_KEY; break;
                        case '3': event.input = InputType::DEL_KEY; break;
                        case '4': event.input = InputType::END_KEY; break;
                        case '5': event.input = InputType::PAGE_UP; break;
                        case '6': event.input = InputType::PAGE_DOWN; break;
                        case '7': event.input = InputType::HOME_KEY; break;
                        case '8': event.input = InputType::END_KEY; break;
                        }
                        return event;
                    }
                }
                else
                {
                    switch (seq[1]) 
                    {
                    case 'A': event.input = InputType::ARROW_UP; break;
                    case 'B': event.input = InputType::ARROW_DOWN; break;
                    case 'C': event.input = InputType::ARROW_RIGHT; break;
                    case 'D': event.input = InputType::ARROW_LEFT; break;
                    case 'F': event.input = InputType::END_KEY; break;
                    case 'H': event.input = InputType::HOME_KEY; break;
                    }
                    return event;
                }
            }
            else if (seq[0] == 'O') 
            {            
                switch (seq[1])
                {
                case 'H': event.input = InputType::HOME_KEY; break;
                case 'F': event.input = InputType::END_KEY; break;
                }
                return event;
            }     
            
            event.input = InputType::ESCAPE;
            return event;     
        }
        
        if (c == ' ')
        {
            event.input = InputType::SPACEBAR;
            return event;
        }

        if (c == '\r')
        {
            event.input = InputType::ENTER;
            return event;
        }

        if (c >= 1 && c <= 26)
        {
            event.modifiers &= InputModifier::Ctrl;
            event.ch = 'a' + (c - 1);
            return event;
        }

        event.input = InputType::CHAR;
        event.ch = c;
        return event;
    }

    void TermiosCore::outputBuffer()
    {
        std::string output;
        
        // output += TermiosUtils::CURSOR_HOME.data();

        GfxUtils::Style prevStyle{};
        prevStyle.fg = GfxUtils::Color::Invalid;
        prevStyle.bg = GfxUtils::Color::Invalid;

        for (size_t r = 0; r < m_buffer.data.rows(); ++r)
        {
            for (size_t c = 0; c < m_buffer.data.cols(); ++c)
            {
                TermiosUtils::appendMoveCursor(output, r, c);

                const auto tch = m_buffer.data(r, c);

                const auto str = TermiosUtils::Termios_TerminalCharToStr(tch, &prevStyle);

                output += str;

                // if (c == m_buffer.data.cols() - 1)
                // {
                //     // end of line
                //     output += TermiosUtils::RESET_COLORS;      // reset colors
                //     output += TermiosUtils::RESET_ATTRS;      // reset attrs

                //     prevStyle.fg = GfxUtils::Color::Invalid;
                //     prevStyle.bg = GfxUtils::Color::Invalid;
                // }
            }
        }

        write(STDOUT_FILENO, output.c_str(), output.size());
        m_buffer.reset();
    }

    void TermiosCore::clearScreen()
    {
        LOG_DEBUG("[TermiosCore] clearing screen immediatly");
        std::string frameStr;
        frameStr += TermiosUtils::CURSOR_HOME;

        for (size_t r = 0; r < m_termConfig.size.height; ++r)
        {
            TermiosUtils::appendMoveCursorTerminalSafe(frameStr, m_termConfig, r, 0);
            frameStr += TermiosUtils::ERASE_LINE_TORIGHT;
        }
        write(STDOUT_FILENO, frameStr.c_str(), frameStr.size());
    }

    void TermiosCore::hideCursor()
    {  
        write(STDOUT_FILENO, TermiosUtils::HIDE_CURSOR.data(), TermiosUtils::HIDE_CURSOR.size());
    }

    void TermiosCore::showCursor()
    {  
        write(STDOUT_FILENO, TermiosUtils::SHOW_CURSOR.data(), TermiosUtils::SHOW_CURSOR.size());
    }

    void TermiosCore::moveCursor(size_t r, size_t c)
    {
        // LOG_DEBUG("[TermiosCore] Move cursor to ( %d, %d )", row, col);
        if (!m_termConfig.size.width || !m_termConfig.size.height)
        {
            return; // todo
        }
        r = std::clamp(r, size_t{0}, m_termConfig.size.height - 1);
        c = std::clamp(c, size_t{0}, m_termConfig.size.width  - 1);

        auto ansi = std::format("\x1b[{};{}H", std::to_string(r + 1), std::to_string(c + 1));

        write(STDOUT_FILENO, ansi.data(), ansi.size());
        
        m_cursorCoord = {r, c};
    }

    void TermiosCore::cursorHome()
    {  
        LOG_DEBUG("[TermiosCore] Cursor home");
        write(STDOUT_FILENO, TermiosUtils::CURSOR_HOME.data(), TermiosUtils::CURSOR_HOME.size());
        
        m_cursorCoord = {0, 0};
    }

    void TermiosCore::render(const Core::MenuData& menuData)
    {        
        LOG_DEBUG("[TermiosCore] Rendering MenuData");

        if (menuData.empty())
        {
            LOG_WARNING("[TermiosCore] render(): Empty menuData");
            return;
        }

        TermiosMenuView menuView;
        size_t height = 20;
        size_t width = 60;

        Core::Geometry::Point start{ 0 + 10, 0 + 10 };
        Core::Geometry::Size size{ width, height };
        Core::Geometry::Rect rect{ start, size };

        menuView.renderToSurface(menuData, m_buffer, rect);
        
        outputBuffer();
    }

    void TermiosCore::render(const Core::Container::Board& board)
    {        
        LOG_DEBUG("[TermiosCore] Rendering Board");

        if (board.empty())
        {
            LOG_WARNING("[TermiosCore] render(): Empty board");
            return;
        }

        TermiosBoardView boardView;
        auto height = board.size().rows;
        auto width = board.size().cols;

        Core::Geometry::Point start{ 0, 0 };
        Core::Geometry::Size size{ width, height };
        Core::Geometry::Rect rect{ start, size };

        boardView.renderToSurface(board, m_buffer, rect);

        outputBuffer();
    }

    void TermiosCore::render(const Core::Help::HelpData& helpData)
    {        
        LOG_DEBUG("[TermiosCore] Rendering HelpData");

        if (helpData.empty())
        {
            LOG_WARNING("[TermiosCore] render(): Empty helpData");
            return;
        }

        TermiosHelpView helpView;
        size_t height = 20;
        size_t width = 60;

        Core::Geometry::Point start{ 0 + 10, 0 + 10 };
        Core::Geometry::Size size{ width, height };
        Core::Geometry::Rect rect{ start, size };

        helpView.renderToSurface(helpData, m_buffer, rect);
        
        outputBuffer();
    }

    bool TermiosCore::enableRawMode()
    {
        LOG_DEBUG("[TermiosCore] Enabling raw mode");

        if (tcgetattr(STDIN_FILENO, &m_orginalTermios) == -1)
        {
            LOG_ERROR("[TermiosCore] Failed: can't enable terminal raw mode.");
            return false;
        }

        struct termios raw = m_orginalTermios;

        // Enabling raw mode (from kilo app)
        raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
        raw.c_oflag &= ~(OPOST);
        raw.c_cflag |= (CS8);
        raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
        // timeout for read
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 1;

        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        {
            LOG_ERROR("[TermiosCore] Failed: can't enable terminal raw mode.");
            return false;
        }

        LOG_DEBUG("[TermiosCore] Raw mode enabled");

        return true;
    }

    bool TermiosCore::disableRawMode()
    {        
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &m_orginalTermios) == -1)
        {
            LOG_ERROR("Failed: can't disable terminal raw mode.");
            return false;
        }

        return true;
    }

    bool TermiosCore::updateCursorPosition()
    {
        try
        {
            std::array<char, 32> buf{};
            size_t i = 0;

            // Send query
            if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) 
            {
                throw std::runtime_error("[TermiosCore] updateCursorPosition() Failed to write cursor query");
            }

            // Read response
            while (i < buf.size() - 1) 
            {
                if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
                if (buf[i] == 'R') break;
                i++;
            }
            buf[i] = '\0';

            // Parse response
            if (buf[0] != '\x1b' || buf[1] != '[') 
            {
                throw std::runtime_error("[TermiosCore] updateCursorPosition() Invalid cursor response");
            }

            int r = 0, c = 0;
            if (sscanf(&buf[2], "%d;%d", &r, &c) != 2) 
            {
                throw std::runtime_error("[TermiosCore] updateCursorPosition() Failed to parse cursor position");
            }

            m_cursorCoord = { static_cast<size_t>(r), static_cast<size_t>(c) };
            return true;
        }
        catch(...)
        {
            return false;
        }
        return false;
    }

    // return true if value was updated
    bool TermiosCore::updateTerminalSize() 
    {
        struct winsize ws;

        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) 
        {
            // Fallback: Move cursor to bottom-right and query position
            try
            {
                if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) 
                {
                    throw std::runtime_error("[TermiosCore] updateTerminalSize() Failed to write fallback query");
                }
                
                auto success = updateCursorPosition();

                if (success)
                {
                    if (m_termConfig.size.height == m_cursorCoord.row && m_termConfig.size.width == m_cursorCoord.col)
                    {
                        return false;
                    }
                    m_termConfig.size.height = m_cursorCoord.row;
                    m_termConfig.size.width = m_cursorCoord.col;
                    return true;
                }

                return false;
            }
            catch(...)
            {
                return false;
            }
            
        }

        if (m_termConfig.size.height == ws.ws_row && m_termConfig.size.width == ws.ws_col)
        {
            return false;
        }
        m_termConfig.size.height = ws.ws_row;
        m_termConfig.size.width = ws.ws_col;

        return true;
    }

    void TermiosCore::updateTerminalConfig() 
    {
        if (updateTerminalSize())
        {
            LOG_DEBUG("[TermiosCore] Terminal size updated");
            m_buffer.resize(m_termConfig.size.height, m_termConfig.size.width);
        }
    }

    void TermiosCore::init()
    {
        LOG_DEBUG("[TermiosCore] Initializing...");

        if (!enableRawMode())
        {
            throw std::runtime_error("[TermiosCore] init() Couldn't init MacOS Terminal.\n");
        }

        updateTerminalConfig();

        clearScreen();
    }

    void TermiosCore::update()
    {
        // LOG_DEBUG("[TermiosCore] Updating...");
        updateTerminalConfig();
    }

    void TermiosCore::terminate() noexcept
    {
        LOG_DEBUG("[TermiosCore] Shutting down...");
        try 
        {      
            showCursor();
            // restore original terminal
            disableRawMode(); 
        }
        catch (...) 
        {
            LOG_ERROR("[TermiosCore] Shutdown failed.\n");
            return;
        }
        LOG_DEBUG("[TermiosCore] Shutdown complete...");
    }

    void TermiosCore::quit() noexcept
	{
		LOG_DEBUG("[TermiosCore] Quitting...");
        // clear screen
        clearScreen(); 
	}
   
}


  // void TermiosCore::render([[maybe_unused]]const App::Grid::Grid2D<App::Grid::Tile<char>>& frame)
    // {        
    //     LOG_DEBUG("[TermiosCore] Rendering Grid2D");
    //     //appendToBuffer(TermiosGrid2DRenderHelper::toString(*this, frame));
    //     outputBuffer();
    // }
        // todo