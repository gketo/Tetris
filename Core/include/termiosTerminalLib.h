#include <termios.h>


namespace Core {

	class TerminalLib 
	{
    public:
        ~TerminalLib()
        {
            disableRawMode(m_fd);
        }

    private:
        void disableRawMode(int fd);
        int enableRawMode(int fd);
        int editorReadKey(int fd);
        int getCursorPosition(int ifd, int ofd, int* rows, int* cols);
        int getWindowSize(int ifd, int ofd, int* rows, int* cols);

        struct termios m_origTermios; /* In order to restore at exit.*/
        bool m_isRawMode{ false };
        int m_fd{};
        int m_rows{};
        int m_cols{};
	}
}

