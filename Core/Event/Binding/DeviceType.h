#pragma once

// ==================== Includes ====================
#include <string_view>

namespace Core
{
    enum class DeviceType 
    {
        None,
        KEYBOARD,
    }; 

    // Helper function to convert DeviceType to string
	inline std::string_view dbg_to_string(DeviceType device)
	{
		switch (device)
		{
		case DeviceType::None:      return "None";
		case DeviceType::KEYBOARD:  return "KEYBOARD";
		}
        return "Unknown";
	}
}
