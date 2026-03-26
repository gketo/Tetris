#include "ITerminalCore.h"

#include "Logger.h"

#include <memory>
#include <optional>
#include <termios.h>
#include <unistd.h>

// NOTE dbg debug : DOESN'T HANDLE TERMINAL RESTORE MODE ON CRASH. TODO

namespace Core {

    class TerminalCore_Mac : public ITerminalCore 
    {
    public:
        ~TerminalCore_Mac()
        {
            disableRawMode();
        }

        std::optional<DeviceEvent> readEvent() const override
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
            event.source = SourceType::terminal;
            event.device = DeviceType::keyboard;
            event.isCtrl = std::iscntrl(c);
            event.key = (std::iscntrl(c) ? c + '@' : static_cast<int>(c));   // map back to letter<
            
            return event;
        }

    private:
        struct termios orginalTermios;

        bool enableRawMode() override
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

        bool disableRawMode() override
        {
            if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orginalTermios) == -1)
            {
                LOG_ERROR("Failed: can't disable terminal raw mode.");
                return false;
            }
            
            return true;
        }
    };

    std::unique_ptr<ITerminalCore> createTerminalCore()
    {
        return std::make_unique<TerminalCore_Mac>();
    }
}