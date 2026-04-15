#include "TerminalCoreTermios.h"

#include "DeviceEvent.h"
#include "Frame2D.h"
#include "KeyCode.h"
#include "Logger.h"
#include "MenuData.h"
#include "RulesData.h"
#include "TermiosFrame2DHelper.h"
#include "TermiosMenuHelper.h"
#include "TermiosUtils.h"

#include <array>
#include <cstdio>
#include <errno.h>
#include <format>
#include <memory>
#include <optional>
#include <stdexcept>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <utility>

#define CTRL_KEY(k) ((k) & 0x1f)

namespace Core::Terminal::Termios {

    std::unique_ptr<ITerminalCore> createTerminalCore()
    {
        return std::make_unique<TerminalCoreTermios>();
    }

    std::optional<DeviceEvent> TerminalCoreTermios::readEvent() const
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
                throw std::runtime_error("Terminal read failed"); // real error
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
                event.code = KeyCode::ESCAPE;
                return event;
            }
            if ((nread = read(STDIN_FILENO, &seq[1], 1)) != 1)
            {
                event.code = KeyCode::ESCAPE;
                return event;
            }                

            if (seq[0] == '[') 
            {
                if (seq[1] >= '0' && seq[1] <= '9') 
                {
                    if (read(STDIN_FILENO, &seq[2], 1) != 1)
                    {
                        event.code = KeyCode::ESCAPE;
                        return event;
                    }
                    if (seq[2] == '~') 
                    {
                        switch (seq[1]) 
                        {
                        case '1': event.code = KeyCode::HOME_KEY; break;
                        case '3': event.code = KeyCode::DEL_KEY; break;
                        case '4': event.code = KeyCode::END_KEY; break;
                        case '5': event.code = KeyCode::PAGE_UP; break;
                        case '6': event.code = KeyCode::PAGE_DOWN; break;
                        case '7': event.code = KeyCode::HOME_KEY; break;
                        case '8': event.code = KeyCode::END_KEY; break;
                        }
                        return event;
                    }
                }
                else
                {
                    switch (seq[1]) 
                    {
                    case 'A': event.code = KeyCode::ARROW_UP; break;
                    case 'B': event.code = KeyCode::ARROW_DOWN; break;
                    case 'C': event.code = KeyCode::ARROW_RIGHT; break;
                    case 'D': event.code = KeyCode::ARROW_LEFT; break;
                    case 'F': event.code = KeyCode::END_KEY; break;
                    case 'H': event.code = KeyCode::HOME_KEY; break;
                    }
                    return event;
                }
            }
            else if (seq[0] == 'O') 
            {            
                switch (seq[1])
                {
                case 'H': event.code = KeyCode::HOME_KEY; break;
                case 'F': event.code = KeyCode::END_KEY; break;
                }
                return event;
            }     
            
            event.code = KeyCode::ESCAPE;
            return event;     
        }
        
        if (c == ' ')
        {
            event.code = KeyCode::SPACEBAR;
            return event;
        }

        if (c == '\r')
        {
            event.code = KeyCode::ENTER;
            return event;
        }

        if (c >= 1 && c <= 26)
        {
            event.modifiers &= KeyModifier::Ctrl;
            event.ch = 'a' + (c - 1);
            return event;
        }

        event.code = KeyCode::CHAR;
        event.ch = c;
        return event;
    }

     void TerminalCoreTermios::render(const Core::MenuData& menuData) const
    {        
        // LOG_DEBUG("[TerminalCoreTermios] Rendering MenuData");
        // todo mise en page
        std::string frameStr{};

        hideCursor(frameStr);
        clearScreen(frameStr);

        frameStr += TermiosMenuRenderHelper::to_string(menuData);

        showCursor(frameStr);

        write(STDOUT_FILENO, frameStr.c_str(), frameStr.size());   
    }

    void TerminalCoreTermios::render(const Game::RulesData& rules) const
    {
        // LOG_DEBUG("[TerminalCoreTermios] Rendering rules");
        // todo mise en page
        std::string frameStr{};

        hideCursor(frameStr);
        clearScreen(frameStr);

        for (const auto& rule : rules.getRules())
        {
            frameStr += rule;
            frameStr += '\r';
            frameStr += '\n';
        }

        write(STDOUT_FILENO, frameStr.c_str(), frameStr.size());   
    }

    void TerminalCoreTermios::render(const Core::Grid2D::Frame2D<char>&frame) const
    {        
        // LOG_DEBUG("[TerminalCoreTermios] Rendering Frame2D");
        
        std::string frameStr{};

        hideCursor(frameStr);
        frameStr += TermiosFrameRenderHelper::to_string(frame);

        write(STDOUT_FILENO, frameStr.c_str(), frameStr.size());    
    }

    bool TerminalCoreTermios::enableRawMode()
    {
        if (tcgetattr(STDIN_FILENO, &orginalTermios) == -1)
        {
            LOG_ERROR("Failed: can't enable terminal raw mode.");
            return false;
        }

        struct termios raw = orginalTermios;

        // enabling raw mode (from kilo app)
        raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
        raw.c_oflag &= ~(OPOST);
        raw.c_cflag |= (CS8);
        raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
        // timeout for read
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 1;

        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        {
            LOG_ERROR("Failed: can't enable terminal raw mode.");
            return false;
        }

        return true;
    }

    bool TerminalCoreTermios::disableRawMode()
    {        
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orginalTermios) == -1)
        {
            LOG_ERROR("Failed: can't disable terminal raw mode.");
            return false;
        }

        return true;
    }

    std::pair<int, int> TerminalCoreTermios::getCursorPosition() const
    {
        std::array<char, 32> buf{};
        size_t i = 0;

        // Send query
        if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) 
        {
            throw std::runtime_error("Failed to write cursor query");
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
            throw std::runtime_error("Invalid cursor response");
        }

        int rows = 0, cols = 0;
        if (sscanf(&buf[2], "%d;%d", &rows, &cols) != 2) 
        {
            throw std::runtime_error("Failed to parse cursor position");
        }

        return {rows, cols};
    }

    bool TerminalCoreTermios::updateCursorPosition()
    {
        try
        {
            auto [row, col] = getCursorPosition();
            m_crow = row;
            m_ccol = col;
            return true;
        }
        catch(...)
        {
            return false;
        }
        return false;
    }

    bool TerminalCoreTermios::updateWindowSize() 
    {
        struct winsize ws;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) 
        {
            // Fallback: Move cursor to bottom-right and query position
            try
            {
                if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) 
                {
                    throw std::runtime_error("Failed to write fallback query");
                }
                auto [maxRow, maxCol] = getCursorPosition();
                m_winHeight = maxRow;
                m_winWidth = maxCol;
                return true;
            }
            catch(...)
            {
                return false;
            }
            
        }
        m_winWidth = ws.ws_row;
        m_winHeight = ws.ws_col;
        return true;
    }

    void TerminalCoreTermios::clearScreen() const
    {
        write(STDOUT_FILENO, CLEAR_SCROLLBACK.data(), CURSOR_HOME.size());
        write(STDOUT_FILENO, CLEAR_SCREEN.data(), CURSOR_HOME.size());
        write(STDOUT_FILENO, CURSOR_HOME.data(), CURSOR_HOME.size());
    }

    void TerminalCoreTermios::hideCursor() const
    {  
        LOG_DEBUG("[TerminalCoreTermios] Hide cursor");
        write(STDOUT_FILENO, HIDE_CURSOR.data(), HIDE_CURSOR.size());
    }

    void TerminalCoreTermios::showCursor() const
    {  
        LOG_DEBUG("[TerminalCoreTermios] Show cursor");
        write(STDOUT_FILENO, SHOW_CURSOR.data(), SHOW_CURSOR.size());
    }

    void TerminalCoreTermios::moveCursor(int row, int col) const
    {
        LOG_DEBUG("[TerminalCoreTermios] Move cursor to ( %d, %d )", row, col);

        row = std::clamp(row, 0, m_winHeight - 1);
        col = std::clamp(col, 0, m_winWidth  - 1);

        auto ansi = std::format("\x1b[{};{}H", std::to_string(row + 1), std::to_string(col + 1));

        write(STDOUT_FILENO, ansi.data(), ansi.size());
    }

    void TerminalCoreTermios::clearScreen(std::string& frameStr) const
    {
        frameStr += CLEAR_SCROLLBACK.data(); // clear scrollback buffer
        frameStr += CLEAR_SCREEN.data(); // clear screen
        frameStr += CURSOR_HOME.data();  // move cursor to home
    }

    void TerminalCoreTermios::hideCursor(std::string& frameStr) const
    {  
        frameStr += HIDE_CURSOR.data();    
    }

    void TerminalCoreTermios::showCursor(std::string& frameStr) const 
    {
        frameStr += SHOW_CURSOR.data();  
    }

    void TerminalCoreTermios::moveCursor(std::string& frameStr, int row, int col) const
    {
        LOG_DEBUG("[TerminalCoreTermios] Move cursor to ( %d, %d )", row, col);

        row = std::clamp(row, 0, m_winHeight - 1);
        col = std::clamp(col, 0, m_winWidth  - 1);

        frameStr.reserve(frameStr.size() + 16);

        frameStr += "\x1b[";
        frameStr += std::to_string(row + 1);
        frameStr += ";";
        frameStr += std::to_string(col + 1);
        frameStr += "H";

        // chatgpt should be faster debug dbg
        // char buf[32];
        // char* ptr = buf;
        // *ptr++ = '\x1b';
        // *ptr++ = '[';
        // auto [p1, _] = std::to_chars(ptr, buf + sizeof(buf), row + 1);
        // ptr = p1;
        // *ptr++ = ';';
        // auto [p2, _2] = std::to_chars(ptr, buf + sizeof(buf), col + 1);
        // ptr = p2;
        // *ptr++ = 'H';
        //frameStr.append(buf, ptr - buf);
    }

    const char* TerminalCoreTermios::caller() const  
    {
        return "TerminalCoreTermios";
    }

    void TerminalCoreTermios::onInit()
    {
        if (!enableRawMode())
        {
            throw std::runtime_error("[ERROR] Couldn't init MacOS Terminal.\n");
        }

        clearScreen();
    }

    void TerminalCoreTermios::onTerminate() noexcept
    {
        LOG_DEBUG("[TerminalCoreTermios] Shutting down...");
        try 
        {      
            showCursor();
            // restore original terminal
            disableRawMode(); 
        }
        catch (...) 
        {
            LOG_ERROR("[TerminalCoreTermios] Shutdown failed.\n");
            return;
        }
        LOG_DEBUG("[TerminalCoreTermios] Shutdown complete...");
    }

    void TerminalCoreTermios::onQuit() noexcept
	{
		LOG_DEBUG("[TerminalCoreTermios] Quitting...");
        // clear screen
        clearScreen(); 
        // save data here
	}
   
} 