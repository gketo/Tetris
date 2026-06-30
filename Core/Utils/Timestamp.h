#pragma once

// ==================== Includes ====================
#include <chrono>

namespace Core {

    struct Timestamp
    {
        using Clock = std::chrono::steady_clock;

        Clock::time_point value;

        Timestamp()
            : value{Clock::now()}
        {}

        auto operator<=>(const Timestamp&) const = default;

        explicit Timestamp(Clock::time_point tp)
            : value{tp}
        {}

        static Timestamp invalid()
        {
            return Timestamp{Clock::time_point::min()};
        }

        bool is_valid() const
        {
            return value != Clock::time_point::min();
        }

        auto to_ms() const
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(value.time_since_epoch()).count();
        }
    };

}