#pragma once

#include "ITerminalCore.h"

#include <memory>
#include <optional>
#include <termios.h>
#include <unistd.h>
#include <utility>

// NOTE dbg debug : DOESN'T HANDLE TERMINAL RESTORE MODE ON CRASH. TODO todo
//todo vertical wrapping
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

        void update() override;
        bool updateTerminalConfig() override;

        void outputBuffer() override;

        void clearScreen() override;
        void hideCursor() override;
        void showCursor() override;
        void moveCursor(size_t row, size_t col) override;
        void cursorHome() override;

        void clearScreen(std::string& framestr) const override;
        void hideCursor(std::string& framestr) const override;
        void showCursor(std::string& framestr) const override;
        void moveCursor(std::string& framestr, size_t row, size_t col) const override;
        void cursorHome(std::string& framestr) const override;

        // rendering
        void render(const Core::MenuData& menuData) override;
        void render(const Game::RulesData& rules) override;
        void render(const Core::Grid2D::Frame2D<char>& frame) override;

    private:
        struct termios orginalTermios;

        bool enableRawMode() override;
        bool disableRawMode() override;

        bool updateCursorPosition() override;
        bool updateTerminalSize() override;
        
        const char* caller() const override; // for clearer logging
        void onInit() override;
        void onTerminate() noexcept override;
		void onQuit() noexcept override;
    };

}