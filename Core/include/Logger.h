#pragma once

// for linux macOs open terminal and type:
// ->     export DEBUG_TTY=$(tty)

#include <cstdarg>
#include <cstdlib>
#include <cstdio>

#ifdef _WIN32
    #include <io.h>
    #include <fcntl.h>
    #define WRITE _write
    #define OPEN  _open
    #define DEFAULT_LOG_PATH "debug.log"
#else
    #include <unistd.h>
    #include <fcntl.h>
    #define WRITE write
    #define OPEN  open
    #define DEFAULT_LOG_PATH nullptr
#endif

namespace Logger {

inline int g_log_fd = -1;

// Lazy init
inline void init(const char* path = nullptr) {
    if (g_log_fd != -1) return;

    if (!path) {
        path = std::getenv("DEBUG_TTY");
    }

    // Fallbacks
    if (!path) {
        path = DEFAULT_LOG_PATH;
    }

    if (path) {
#ifdef _WIN32
        g_log_fd = OPEN(path, _O_WRONLY | _O_CREAT | _O_APPEND);
#else
        g_log_fd = OPEN(path, O_WRONLY | O_CLOEXEC);
#endif
    }
}

// Ensure initialized automatically
inline void ensure_init() {
    if (g_log_fd == -1) {
        init();
    }
}

// Core logging (fast, stack buffer only)
inline void log(const char* level, const char* fmt, ...) {
    ensure_init();
    if (g_log_fd == -1) return;

    char buffer[1024];

    int offset = snprintf(buffer, sizeof(buffer), "[%s] ", level);

    va_list args;
    va_start(args, fmt);
    int msg_len = vsnprintf(buffer + offset, sizeof(buffer) - offset, fmt, args);
    va_end(args);

    int total = offset + msg_len;

    if (total < (int)sizeof(buffer) - 1) {
        buffer[total++] = '\n';
    }

    WRITE(g_log_fd, buffer, total);
}

// Macros
#define LOG_DEBUG(fmt, ...)   Logger::log("DEBUG", fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)    Logger::log("INFO", fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) Logger::log("WARNING", fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)   Logger::log("ERROR", fmt, ##__VA_ARGS__)

} // namespace Logger