#ifdef EXCLUDE_THIS_FILE


#include "TerminalLib.h"


namespace Core {
    void disableRawMode() {
        /* Don't even check the return value as it's too late. */
        if (m_isRawMode) {
            tcsetattr(m_fd, TCSAFLUSH, &m_origTermios);
            m_isRawMode = false;
        }
    }

    /* Raw mode: 1960 magic shit. */
    int enableRawMode() {
        struct termios raw;

        if (m_isRawMode)
        {
            return 0;
        }

        if (!isatty(m_fd))
        {
            throw std::runtime_error("enableRawMode fd error");
        }
        
        if (tcgetattr(m_fd, &orig_termios) == -1)
        {
            throw std::runtime_error("enableRawMode fd error");
        }

        raw = m_origTermios;  /* modify the original mode */

        /* input modes: no break, no CR to NL, no parity check, no strip char,
         * no start/stop output control. */
        raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

        /* output modes - disable post processing */
        raw.c_oflag &= ~(OPOST);

        /* control modes - set 8 bit chars */
        raw.c_cflag |= (CS8);

        /* local modes - choing off, canonical off, no extended functions,
         * no signal chars (^Z,^C) */
        raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

        /* control chars - set return condition: min number of bytes and timer. */
        raw.c_cc[VMIN] = 0; /* Return each byte, or zero for timeout. */
        raw.c_cc[VTIME] = 1; /* 100 ms timeout (unit is tens of second). */

        /* put terminal in raw mode after flushing */
        if (tcsetattr(m_fd, TCSAFLUSH, &raw) < 0)
        {
            throw std::runtime_error("fd error");
        }

        m_isRawMode = 1;
        return 0;
    }
    
    /* Read a key from the terminal put in raw mode, trying to handle
     * escape sequences. */
  

    /* Use the ESC [6n escape sequence to query the horizontal cursor position
     * and return it. On error -1 is returned, on success the position of the
     * cursor is stored at *rows and *cols and 0 is returned. */
    int getCursorPosition(int ifd, int ofd) {
        char buf[32];
        unsigned int i = 0;

        /* Report cursor location */
        if (write(ofd, "\x1b[6n", 4) != 4) return -1;

        /* Read the response: ESC [ rows ; cols R */
        while (i < sizeof(buf) - 1) {
            if (read(ifd, buf + i, 1) != 1) break;
            if (buf[i] == 'R') break;
            i++;
        }
        buf[i] = '\0';

        /* Parse it. */
        if (buf[0] != ESC || buf[1] != '[') return -1;
        if (sscanf(buf + 2, "%d;%d", m_rows, m_cols) != 2) return -1;
        return 0;
    }

    /* Try to get the number of columns in the current terminal. If the ioctl()
     * call fails the function will try to query the terminal itself.
     * Returns 0 on success, -1 on error. */
    int getWindowSize(int ifd, int ofd) {
        struct winsize ws;

        if (ioctl(1, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
            /* ioctl() failed. Try to query the terminal itself. */
            int orig_row, orig_col, retval;

            /* Get the initial position so we can restore it later. */
            retval = getCursorPosition(ifd, ofd, &orig_row, &orig_col);
            if (retval == -1) goto failed;

            /* Go to right/bottom margin and get position. */
            if (write(ofd, "\x1b[999C\x1b[999B", 12) != 12) goto failed;
            retval = getCursorPosition(ifd, ofd);
            if (retval == -1) goto failed;

            /* Restore position. */
            char seq[32];
            snprintf(seq, 32, "\x1b[%d;%dH", orig_row, orig_col);
            if (write(ofd, seq, strlen(seq)) == -1) {
                /* Can't recover... */
            }
            return 0;
        }
        else {
            m_cols = ws.ws_col;
            m_rows = ws.ws_row;
            return 0;
        }

    failed:
        return -1;
    }
}

#endif