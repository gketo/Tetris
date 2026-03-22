#ifndef CTRL_INTERFACE_H
#define CTRL_INTERFACE_H

#include <iostream>
#include <string>
#include <windows.h>

namespace Core {

	constexpr enum class DeviceType 
	{
		None,
		keyboard,
		Count
	};

	constexpr enum class KeyCode
	{
		None,
		// keyboard
		key_escape = 27,
		ctrl_p = 80,
		ctrl_q = 81,
		spacebar = 32
		//
	};

	// Helper function to convert DeviceType enum to string
	inline std::string to_string(DeviceType device)
	{
		switch (device)
		{
		case DeviceType::keyboard: return "keyboard";
		case DeviceType::None: return "None";
		default: return "Unknown";
		}
	}

	// Helper function to convert KeyCode enum to string
	inline std::string to_string(KeyCode keyCode)
	{
		switch (keyCode)
		{
		case KeyCode::key_escape: return "Escape";
		case KeyCode::ctrl_p: return "Ctrl+P";
		case KeyCode::ctrl_q: return "Ctrl+Q";
		case KeyCode::spacebar: return "Spacebar";
		case KeyCode::None: return "None";
		default: return "Unknown";
		}
	}

	struct InputEvent
	{
		bool isValid;
		DeviceType device;
		KeyCode keyCode;

		void print() const
		{
			std::cout << "CtrlInterface event -> Device: " << to_string(device) << ", KeyCode: " << to_string(keyCode) << ", isValid: " << isValid << "\n";
		}
	};


	class CtrlInterface
	{
	public:
		CtrlInterface(DeviceType device)
			: m_currentDevice{ device }
		{
		}

		virtual ~CtrlInterface() = default;

		InputEvent onEvent(bool lockpolling)
		{
			std::cout << "CtrlInterface onEvent()\n";

			return readUserEvent(lockpolling);

			// todo
			// check input stream
			// if input event
				// verify input event
				// return input event
			//else
				// return Null.
		}

		virtual InputEvent readUserEvent(bool lockpolling) const = 0;

	protected:
		DeviceType m_currentDevice{};
	};
}

#endif