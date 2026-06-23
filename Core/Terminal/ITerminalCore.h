#pragma once

#include "Core/Types/Index2D.h"
#include "Core/Event/Source/IEventSource.h"
#include "Core/Render/IRenderer.h"
#include "Core/Terminal/TerminalSurface.h"
#include "Core/Terminal/TerminalConfig.h"

#include <cstddef>
#include <memory>
#include <mutex>
#include <string>

// todo mutex
namespace Core::Terminal {

	class ITerminalCore : public IEventSource, public IRenderer
	{
    public:
        virtual ~ITerminalCore() = default;

        virtual void outputBuffer() = 0;

        // Grid::GridCoord getCursorCoord() const { return m_cursorCoord; }
        TerminalConfig getTerminalConfig() const { return m_termConfig; }

        virtual void hideCursor() = 0;
        virtual void showCursor() = 0;
        virtual void moveCursor(size_t r, size_t c) = 0;
        virtual void cursorHome() = 0;

    protected:
        Core::Type::Index2D m_cursorCoord;
        TerminalConfig m_termConfig;

        std::mutex m_bufferMutex;
        TerminalSurface m_buffer;

        virtual bool enableRawMode() = 0;
        virtual bool disableRawMode() = 0;

        virtual bool updateCursorPosition() = 0;
        virtual bool updateTerminalSize() = 0;
        virtual void updateTerminalConfig() = 0;

	};

    std::unique_ptr<ITerminalCore> createTerminalCore();
}
