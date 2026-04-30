#pragma once

#include "IEventSource.h"
#include "IRenderer.h"

#include <cstddef>
#include <memory>
#include <mutex>
#include <string>

// todo mutex
namespace Core {

    struct CursorPosition 
    {
        size_t row;
        size_t col;   
    };

    struct TerminalConfig
    {
        size_t height;
        size_t width;
    };

	class ITerminalCore : public IEventSource, public IRenderer
	{
    public:
        virtual ~ITerminalCore() = default;

        virtual bool updateTerminalConfig() = 0;

        void appendToBuffer(const std::string& str);
        void flushBuffer();
        virtual void outputBuffer() = 0;

        CursorPosition getCursorPosition() const { return m_cpos; }
        TerminalConfig getTerminalConfig() const { return m_termConfig; }

        virtual void hideCursor() = 0;
        virtual void showCursor() = 0;
        virtual void moveCursor(size_t row, size_t col) = 0;
        virtual void cursorHome() = 0;

        virtual void clearScreen(std::string& framestr) const = 0;
        virtual void hideCursor(std::string& framestr) const = 0;
        virtual void showCursor(std::string& framestr) const = 0;
        virtual void moveCursor(std::string& framestr, size_t row, size_t col) const = 0;
        virtual void cursorHome(std::string& framestr) const = 0;

    protected:
        CursorPosition m_cpos;
        TerminalConfig m_termConfig;

        std::string m_bufferStr;
        std::mutex m_bufferMutex;

        virtual bool enableRawMode() = 0;
        virtual bool disableRawMode() = 0;

        virtual bool updateCursorPosition() = 0;
        virtual bool updateTerminalSize() = 0;
	};
 
    inline void ITerminalCore::appendToBuffer(const std::string& str)
    {
        std::lock_guard<std::mutex> lock(m_bufferMutex);
        m_bufferStr += str;
    }

    inline void ITerminalCore::flushBuffer()
    {
        std::lock_guard<std::mutex> lock(m_bufferMutex);
        m_bufferStr.clear();
    }

    std::unique_ptr<ITerminalCore> createTerminalCore();

}
