#include "TerminalLib.h"


namespace Core {
    void TerminalLib::enableRawMode()
    {
        HANDLE hStdin = GetStdHandle(m_consInputDevice);
        DWORD mode;
        GetConsoleMode(hStdin, &mode);

        // save orignal mode and terminal
        m_consOrigMode = mode;

        // Disable line input and echo (raw-like)
        mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);

        SetConsoleMode(hStdin, mode);

        m_hStdin = hStdin;
        m_isRawModeActive = true;

        std::cout << "console raw mode enabled\n";
    }

    void TerminalLib::disableRawMode()
    {
        SetConsoleMode(m_hStdin, m_consOrigMode);
        m_isRawModeActive = false;
        std::cout << "console raw mode disabled\n";
    }

    std::optional<WORD> TerminalLib::read(bool readlock)
    {
        INPUT_RECORD rec;
        DWORD byte_read;
        
        //while (ReadConsoleInput(m_hStdin, &rec, 1, &byte_read) == 0); this is a blocking loop waiting for user input

        while (readlock)
        {
            ReadConsoleInput(m_hStdin, &rec, 1, &byte_read);

            if (rec.EventType == KEY_EVENT && rec.Event.KeyEvent.bKeyDown && byte_read == 1)
            {
                WORD c = rec.Event.KeyEvent.wVirtualKeyCode;
             
                std::cout << "Key: 0x" << std::hex << c << "\n";

                return c;
            }
        }

        return std::nullopt;
    }
}