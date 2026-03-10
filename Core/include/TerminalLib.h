
#include <iostream>
#include <optional>
#include <windows.h>

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

        std::optional<WORD> read(bool readlock);

        //int editorReadKey(int fd);
        //int getCursorPosition(int ifd, int ofd, int* rows, int* cols);
        //int getWindowSize(int ifd, int ofd, int* rows, int* cols);
       

    private:
        bool m_isRawModeActive{ false };
        DWORD m_consInputDevice;
        HANDLE m_hStdin{};
        DWORD m_consOrigMode{};

        //int m_rows{};
        //int m_cols{};
    };


}

