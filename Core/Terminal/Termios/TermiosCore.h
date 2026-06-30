#pragma once

// ==================== Includes ====================
#include "Core/Terminal/ITerminalCore.h"

// ==================== Includes ====================
#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <termios.h>

// NOTE dbg debug : DOESN'T HANDLE TERMINAL RESTORE MODE ON CRASH. TODO todo

namespace Core {
    class MenuData; // forward declaration
}

namespace Core::Container {
    class Board;    // forward declaration
}

namespace Core::Terminal::Termios {
    
    // non-member function
    std::unique_ptr<ITerminalCore> createTerminalCore();

    class TermiosCore : public ITerminalCore 
    {
    public:
        std::optional<DeviceEvent> readEvent() const override;

        void outputBuffer() override;

        void clearScreen() override;
        void hideCursor() override;
        void showCursor() override;
        void moveCursor(size_t r, size_t c) override;
        void cursorHome() override;

        void init() override;
        void update() override;
        void terminate() noexcept override;
		void quit() noexcept override;
        
        // rendering
        void render(const Core::MenuData& menuData) override;
        void render(const Core::Container::Board& board) override;
        void render(const Core::Help::HelpData& helpData) override;

    private:
        struct termios m_orginalTermios;

        bool enableRawMode() override;
        bool disableRawMode() override;

        bool updateCursorPosition() override;
        bool updateTerminalSize() override;
        void updateTerminalConfig() override;

    };

}