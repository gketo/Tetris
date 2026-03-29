#pragma once

#include "ITerminalCore.h"

#include <memory>
#include <optional>
#include <termios.h>
#include <unistd.h>

// NOTE dbg debug : DOESN'T HANDLE TERMINAL RESTORE MODE ON CRASH. TODO todo

namespace Core {

    class Frame2D;

    class TerminalCore_Mac : public ITerminalCore 
    {
    public:
        std::optional<DeviceEvent> readEvent() const override;
        
        void render(const Frame2D& frame) const override;

    private:
        struct termios orginalTermios;
        int winHeight;   // windows height in rows (starts at 1 in termios)
        int winWidth;   // windows width in cols (starts at 1 in termios)
        // int crow;   // cursor pos
        // int ccol;   // cursor pos

        bool enableRawMode() override;
        bool disableRawMode() override;

        void clearScreen(std::string& framestr) const;
        void hideCursor(std::string& framestr) const;
        void showCursor(std::string& framestr) const;
        void moveCursor(std::string& framestr, int row, int col) const;
        
    };

    std::unique_ptr<ITerminalCore> createTerminalCore();
}