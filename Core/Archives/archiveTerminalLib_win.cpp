#ifdef EXCLUDE_THIS_FILE

#include "TerminalLib.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>

namespace Core {

    struct TerminalRawEventWin
    {
        bool isValid;           // valid or invalid event
        WORD code;              // virtual key or device code
        DWORD controlState;     // modifier / control bits
        bool pressed;           // key down or up
    };

    class TerminalLibWin : public TerminalLib
    {
        void enableRawMode()
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

        void disableRawMode()
        {
            SetConsoleMode(m_hStdin, m_consOrigMode);
            m_isRawModeActive = false;
            std::cout << "console raw mode disabled\n";
        }

        TerminalRawEvent readUserEvent(bool lockpolling) const
        {
            INPUT_RECORD rec;
            DWORD byte_read;
            
            TerminalRawEvent rawEvent;

            //while (ReadConsoleInput(m_hStdin, &rec, 1, &byte_read) == 0); this is a blocking loop waiting for user input
            while (lockpolling)
            {
                ReadConsoleInput(m_hStdin, &rec, 1, &byte_read);

                if (rec.EventType == KEY_EVENT && rec.Event.KeyEvent.bKeyDown && byte_read == 1)
                {
                    rawEvent.code = rec.Event.KeyEvent.wVirtualKeyCode;
                    rawEvent.controlState = rec.Event.KeyEvent.dwControlKeyState;
                    rawEvent.pressed = rec.Event.KeyEvent.bKeyDown;

                    rawEvent.isValid = true;

                    return rawEvent;
                }
            }

            rawEvent.isValid = false;

            return rawEvent;
        }
    }
    
}

#endif

#endif