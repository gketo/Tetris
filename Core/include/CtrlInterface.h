#ifndef CTRL_INTERFACE_H
#define CTRL_INTERFACE_H

#include <iostream>
#include <string>
#include <windows.h>

namespace Core {

	enum class DeviceType 
	{
		None,
		keyboard,
		max_device_type
	};

	enum class InputCode
	{
		None,
		spacebar,
		escape,
		max_input_type
	};

	struct InputEvent
	{
		DeviceType device;
		InputCode input;
	};

	class CtrlInterface
	{
	public:
		CtrlInterface(DeviceType device)
			: m_currentDevice{device}
		{ }

		virtual ~CtrlInterface() = default;

		InputEvent onEvent()
		{
			std::cout << "CtrlInterface onEvent()\n";

			// todo
			// check input stream
			// if input event
				// verify input event
				// return input event
			//else
				// return Null.
			return { m_currentDevice, InputCode::None };
		}

		virtual InputEvent interpretTerminalRead(WORD read) = 0;

	protected:
		DeviceType m_currentDevice{};	
	};
}

#endif