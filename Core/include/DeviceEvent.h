#pragma once

#include <format>
#include <string>
#include <string_view>

namespace Core {

    enum class SourceType
    {
        terminal,
        None
    };

    enum class DeviceType 
	{
		None,
		keyboard,
		Count
	};

	enum class KeyCode
	{
		None,
		// keyboard
		key_escape,
		ctrl_P,
		ctrl_Q,
		key_P,
		key_Q,
		key_R,
		spacebar,
		arrow_up
		//
	};

    // Helper function to convert SourceType enum to string
	inline std::string_view source_to_string(SourceType source)
	{
		switch (source)
		{
		case SourceType::terminal: return "terminal";
		case SourceType::None: return "None";
		default: return "Unknown";
		}
	}

    // Helper function to convert DeviceType enum to string
	inline std::string_view device_to_string(DeviceType device)
	{
		switch (device)
		{
		case DeviceType::keyboard: return "keyboard";
		case DeviceType::None: return "None";
		default: return "Unknown";
		}
	}

    // Helper function to convert KeyCode enum to string
	inline std::string_view keycode_to_string(KeyCode keyCode)
	{
		switch (keyCode)
		{
		case KeyCode::key_escape: return "Escape";
		case KeyCode::ctrl_P: return "Ctrl+P";
		case KeyCode::ctrl_Q: return "Ctrl+Q";
		case KeyCode::key_P: return "Key_P";
		case KeyCode::key_Q: return "Key_Q";
		case KeyCode::key_R: return "Key_R";
		case KeyCode::spacebar: return "Spacebar";
		case KeyCode::arrow_up: return "ArrowUp";
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