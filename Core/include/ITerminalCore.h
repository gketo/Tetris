#pragma once

#include "DeviceEvent.h"
#include "IEventSource.h"
#include "IRenderer.h"
#include "Lifecycle.h"
#include "Logger.h"

#include <memory>
#include <optional>
#include <utility>

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

namespace Core {

	class ITerminalCore : public IEventSource, public IRenderer
	{
    public:
        virtual ~ITerminalCore() = default;

        // rendering
        virtual void render(const Core::MenuData& menuData) const = 0;
        virtual void render(const Game::RulesData& rules) const = 0;
        virtual void render(const Core::Grid2D::Frame2D<char>&frame) const = 0;

    protected:
        int m_winHeight;   // windows height in rows (starts at 1 in termios)
        int m_winWidth;   // windows width in cols (starts at 1 in termios)
        int m_crow;   // cursor pos
        int m_ccol;   // cursor pos

        virtual bool enableRawMode() = 0;
        virtual bool disableRawMode() = 0;
        
        virtual std::pair<int, int> getCursorPosition() const = 0;
        virtual bool updateCursorPosition() = 0;
        virtual bool updateWindowSize() = 0;

        virtual void clearScreen() const = 0;
        virtual void hideCursor() const = 0;
        virtual void showCursor() const = 0;
        virtual void moveCursor(int row, int col) const = 0;
	};
 
    std::unique_ptr<ITerminalCore> createTerminalCore();

}
