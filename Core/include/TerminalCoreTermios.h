#pragma once

#include "ITerminalCore.h"

#include <memory>
#include <optional>
#include <termios.h>
#include <unistd.h>
#include <utility>

// NOTE dbg debug : DOESN'T HANDLE TERMINAL RESTORE MODE ON CRASH. TODO todo

// forward declaration
namespace Core {
    class MenuData;
}

namespace Game {
    class RulesData;
}

namespace Core::Grid2D {
    template<typename T>
    class Frame2D;
}

namespace Core::Terminal::Termios {
    
    // non member function
    std::unique_ptr<ITerminalCore> createTerminalCore();

    class TerminalCoreTermios : public ITerminalCore 
    {
    public:
        std::optional<DeviceEvent> readEvent() const override;
        
        // rendering
        void render(const Core::MenuData& menuData) const override;
        void render(const Game::RulesData& rules) const override;
        void render(const Core::Grid2D::Frame2D<char>&frame) const override;

    private:
        struct termios orginalTermios;

        bool enableRawMode() override;
        bool disableRawMode() override;

        std::pair<int, int> getCursorPosition() const override;
        bool updateCursorPosition() override;
        bool updateWindowSize() override;

        void clearScreen() const override;
        void hideCursor() const override;
        void showCursor() const override;
        void moveCursor(int row, int col) const override;
        
        void clearScreen(std::string& framestr) const;
        void hideCursor(std::string& framestr) const;
        void showCursor(std::string& framestr) const;
        void moveCursor(std::string& framestr, int row, int col) const;
        
        const char* caller() const override; // for clearer logging
        void onInit() override;
        void onTerminate() noexcept override;
		void onQuit() noexcept override;
    };

}