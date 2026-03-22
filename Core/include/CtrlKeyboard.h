#ifndef CTRL_KEYBOARD_H
#define CTRL_KEYBOARD_H

#include "CtrlInterface.h"
#include "TerminalLib.h"


namespace Core {

	class CtrlKeyboard : public CtrlInterface {
	public:
		CtrlKeyboard(DeviceType device, const TerminalLib& terminal)
			: CtrlInterface{ device }
			, m_terminalLib{ terminal }
		{ }

		// if ctrl and event.code == 17, only ctrl was pressed, else event.code = key pressed (ex. u = 85, ctrl + u = 85)
		InputEvent readUserEvent(bool lockpolling) const override;

	private:
		const TerminalLib& m_terminalLib;
	};
}

#endif