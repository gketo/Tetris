#pragma once

// for linux/macOS open terminal and type:
// -> export DEBUG_TTY=$(tty)

#include <cstdarg>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#ifdef _WIN32
    #include <io.h>
    #include <fcntl.h>

    #define WRITE  _write
    #define OPEN   _open
    #define ISATTY _isatty

    #define DEFAULT_LOG_PATH "debug.log"
#else
    #include <unistd.h>
    #include <fcntl.h>

    #define WRITE  write
    #define OPEN   open
    #define ISATTY isatty

    #define DEFAULT_LOG_PATH nullptr
#endif

namespace Logger {

inline int  g_log_fd = -1;
inline bool g_use_colors = false;

// ------------------------------
// Level definitions (single source of truth)
inline constexpr const char* LEVELS[] = {
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR",
    "EXTRA"
};

constexpr int compute_max_level_width()
{
    int max_len = 0;
    for (auto l : LEVELS)
    {
        int len = 0;
        while (l[len]) ++len;
        if (len > max_len)
            max_len = len;
    }
    return max_len;
}

constexpr int LEVEL_PAD_WIDTH = compute_max_level_width();
// ------------------------------

inline const char* level_color(const char* level)
{
    if (std::strcmp(level, "DEBUG") == 0)
        return "\033[37m"; // green

    if (std::strcmp(level, "INFO") == 0)
        return "\033[92m"; // white

    if (std::strcmp(level, "WARNING") == 0)
        return "\033[33m"; // yellow/orange

    if (std::strcmp(level, "ERROR") == 0)
        return "\033[31m"; // red

    if (std::strcmp(level, "EXTRA") == 0)
        return "\033[36m"; // cyan

    return "\033[0m";
}

// Lazy init
inline void init(const char* path = nullptr)
{
    if (g_log_fd != -1)
        return;

    bool using_tty = false;

    if (!path)
    {
        path = std::getenv("DEBUG_TTY");

        if (path)
            using_tty = true;
    }

    if (!path)
    {
        path = DEFAULT_LOG_PATH;
    }

    if (!path)
        return;

#ifdef _WIN32
    g_log_fd = OPEN(path, _O_WRONLY | _O_CREAT | _O_APPEND);
#else
    g_log_fd = OPEN(path, O_WRONLY | O_CLOEXEC);
#endif

    if (g_log_fd != -1)
    {
        g_use_colors = using_tty;
    }
}

inline void ensure_init()
{
    if (g_log_fd == -1)
    {
        init();
    }
}

// Core logging
inline void log(const char* level, const char* fmt, ...)
{
    ensure_init();

    if (g_log_fd == -1)
        return;

    constexpr const char* RESET = "\033[0m";

    char buffer[4096];

    int offset = 0;

    // Prefix
    if (g_use_colors)
    {
        const char* color = level_color(level);

        offset = snprintf(
            buffer,
            sizeof(buffer),
            "%s[%s]",
            color,
            level
        );
    }
    else
    {
        offset = snprintf(
            buffer,
            sizeof(buffer),
            "[%s]",
            level
        );
    }

    // ---------------- padding (auto-aligned) ----------------
    int level_len = (int)std::strlen(level);
    int pad = LEVEL_PAD_WIDTH - level_len;

    if (pad < 1) pad = 1;

    for (int i = 0; i < pad && offset < (int)sizeof(buffer) - 1; ++i)
    {
        buffer[offset++] = ' ';
    }
    // --------------------------------------------------------

    va_list args;
    va_start(args, fmt);

    int msg_len = vsnprintf(
        buffer + offset,
        sizeof(buffer) - offset,
        fmt,
        args
    );

    va_end(args);

    if (msg_len < 0)
        return;

    int total = offset + msg_len;

    if (g_use_colors)
    {
        total += snprintf(
            buffer + total,
            sizeof(buffer) - total,
            "%s",
            RESET
        );
    }

    if (total < (int)sizeof(buffer) - 1)
    {
        buffer[total++] = '\n';
    }

    WRITE(g_log_fd, buffer, total);
}

// Macros
#define LOG_DEBUG(fmt, ...) \
    Logger::log("DEBUG", fmt __VA_OPT__(,) __VA_ARGS__)

#define LOG_INFO(fmt, ...) \
    Logger::log("INFO", fmt __VA_OPT__(,) __VA_ARGS__)

#define LOG_WARNING(fmt, ...) \
    Logger::log("WARNING", fmt __VA_OPT__(,) __VA_ARGS__)

#define LOG_ERROR(fmt, ...) \
    Logger::log("ERROR", fmt __VA_OPT__(,) __VA_ARGS__)

#ifdef LOG_EXTRA
    #define LOG_EXTRA(fmt, ...) \
        Logger::log("EXTRA", fmt __VA_OPT__(,) __VA_ARGS__)
#else
    #define LOG_EXTRA(fmt, ...) ((void)0)
#endif

} // namespace Logger