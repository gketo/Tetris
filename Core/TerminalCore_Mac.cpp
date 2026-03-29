#include "TerminalCore_Mac.h"

#include "Frame2D.h"
#include "Logger.h"
#include "Frame2DUtils.h"

#include <format>
#include <memory>
#include <optional>
#include <termios.h>

namespace Core {

    std::unique_ptr<ITerminalCore> createTerminalCore()
    {
        return std::make_unique<TerminalCore_Mac>();
    }

    std::optional<DeviceEvent> TerminalCore_Mac::readEvent() const
    {
        DeviceEvent event;

        char c;
        ssize_t n = read(STDIN_FILENO, &c, 1);

        if (n == 0)
        {
            return std::nullopt;
        }
        else if (n == -1)
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
        event.source = SourceType::TERMINAL;
        event.device = DeviceType::KEYBOARD;
        event.isCtrl = std::iscntrl(c);
        event.key = (std::iscntrl(c) ? c + '@' : static_cast<int>(c)); // map back to letter<

        return event;
    }

    void TerminalCore_Mac::render(const Frame2D& frame) const
    {        
        std::string frameStr{};
        
        clearScreen(frameStr);

        frameStr += Frame2DUtils::to_string(frame);
        
        write(STDOUT_FILENO, frameStr.c_str(), frameStr.size());    
    }

    bool TerminalCore_Mac::enableRawMode()
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

    bool TerminalCore_Mac::disableRawMode()
    {
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orginalTermios) == -1)
        {
            LOG_ERROR("Failed: can't disable terminal raw mode.");
            return false;
        }

        return true;
    }

    void TerminalCore_Mac::clearScreen(std::string& frameStr) const
    {
        frameStr += "\x1b[3J"; // clear scrollback buffer
        frameStr += "\x1b[2J"; // clear screen
        frameStr += "\x1b[H";  // move cursor to home
    }

    void TerminalCore_Mac::hideCursor(std::string& frameStr) const
    {  
        frameStr += "\x1b[?25l";    
    }

    void TerminalCore_Mac::showCursor(std::string& frameStr) const 
    {
        frameStr += "\x1b[?25h";  
    }

    void TerminalCore_Mac::moveCursor(std::string& frameStr, int row, int col) const
    {
        row = std::clamp(row, 0, winHeight - 1);
        col = std::clamp(col, 0, winWidth  - 1);

        frameStr.reserve(frameStr.size() + 16);

        frameStr += "\x1b[";
        frameStr += std::to_string(row + 1);
        frameStr += ";";
        frameStr += std::to_string(col + 1);
        frameStr += "H";

        char buf[32];

        // chatgpt should be faster debug dbg
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
}