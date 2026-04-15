#pragma once

#include <string_view>

namespace Core
{
    enum class DeviceType 
    {
        None,
        KEYBOARD,
    }; 

    // Helper function to convert DeviceType enum to string
	inline std::string_view device_to_string(DeviceType device)
	{
		switch (device)
		{
		case DeviceType::None: return "None";
		case DeviceType::KEYBOARD: return "KEYBOARD";
		}
	}
}
