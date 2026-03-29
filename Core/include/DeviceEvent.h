#pragma once

#include <format>
#include <string>
#include <string_view>

namespace Core {

    enum class SourceType
    {
        TERMINAL,
        None
    };

    enum class DeviceType 
	{
		None,
		KEYBOARD,
		Count
	};

	enum class KeyCode
	{
		None,
		// keyboard
		KEY_ESCAPE,
		CTRL_P,
		CTRL_Q,
		KEY_P,
		KEY_Q,
		KEY_R,
		SPACEBAR,
		ARROW_UP
		//
	};

	// Helper function to convert SourceType enum to string
	inline std::string_view source_to_string(SourceType source)
	{
		switch (source)
		{
		case SourceType::TERMINAL: return "TERMINAL";
		case SourceType::None: return "None";
		default: return "Unknown";
		}
	}

    // Helper function to convert DeviceType enum to string
	inline std::string_view device_to_string(DeviceType device)
	{
		switch (device)
		{
		case DeviceType::KEYBOARD: return "KEYBOARD";
		case DeviceType::None: return "None";
		default: return "Unknown";
		}
	}

    // Helper function to convert KeyCode enum to string
	inline std::string_view keycode_to_string(KeyCode keyCode)
	{
		switch (keyCode)
		{
		case KeyCode::KEY_ESCAPE: return "ESCAPE";
		case KeyCode::CTRL_P: return "CTRL_P";
		case KeyCode::CTRL_Q: return "CTRL_Q";
		case KeyCode::KEY_P: return "key_P";
		case KeyCode::KEY_Q: return "key_Q";
		case KeyCode::KEY_R: return "key_R";
		case KeyCode::SPACEBAR: return "SPACEBAR";
		case KeyCode::ARROW_UP: return "ARROW_UP";
		case KeyCode::None: return "None";
		default: return "Unknown";
		}
	}

    struct DeviceEvent
    {
        SourceType source{ SourceType::None };
        DeviceType device{ DeviceType::None };
        bool isCtrl{ false };
        int key{ -1 };

        std::string to_string() const
        {
            return std::format("[DeviceEvent] -> Source: {}, Device: {}, isCtrl: {}, key: {}", source_to_string(source), device_to_string(device), isCtrl, key);
        }
    };
}