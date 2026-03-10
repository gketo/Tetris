#ifndef CTRL_KEYBOARD_INTERFACE_H
#define CTRL_KEYBOARD_INTERFACE_H

#include "CtrlInterface.h"

#include <iostream>

namespace Core {

	class CtrlKeyboard : public CtrlInterface
	{
	public:

		InputEvent onEvent() override
		{
			std::cout << "Keyboard Event\n";
		}
	};
}

#endif