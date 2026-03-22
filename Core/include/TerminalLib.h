#ifndef TERMINAL_LIB_H
#define TERMINAL_LIB_H

#include <iostream>
#include <windows.h>

namespace Core {

    struct TerminalRawEvent
    {
        bool isValid;           // valid or unvalid event
        WORD code;              // virtual key or device code
        DWORD controlState;     // modifier / control bits
        bool pressed;           // key down or up
    };

    class TerminalLib
    {
    public:
        TerminalLib(DWORD consoleInputDevice)
            : m_consInputDevice{ consoleInputDevice }
        { }

        ~TerminalLib()
        {
            disableRawMode();
        }

        void enableRawMode();
        void disableRawMode();

        TerminalRawEvent readUserEvent(bool lockpolling) const;

    private:
        bool m_isRawModeActive{ false };
        DWORD m_consInputDevice;
        HANDLE m_hStdin{};
        DWORD m_consOrigMode{};
    };


}

#endif