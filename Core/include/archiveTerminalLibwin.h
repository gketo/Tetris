#ifdef EXCLUDE_THIS_FILE

#pragma once

namespace Core {



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