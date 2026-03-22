#include "CtrlKeyboard.h"

namespace Core {

	InputEvent CtrlKeyboard::readUserEvent(bool lockpolling) const
	{
		TerminalRawEvent rawEvent = m_terminalLib.readUserEvent(lockpolling);
		
		InputEvent UNVALID_EVENT{ false, m_currentDevice, KeyCode::None };

		if (!rawEvent.isValid)
		{
			return UNVALID_EVENT;
		}

		bool ctrl = (rawEvent.controlState & (LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED)) != 0;
		//bool shift = (event.controlState & SHIFT_PRESSED) != 0;
		//bool alt = (event.controlState & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED)) != 0;

		switch (rawEvent.code)
		{ // interpret as ASCII int 
		case 'P':
			if (ctrl)
				return { true, m_currentDevice, KeyCode::ctrl_p };
			break;
		case 'Q':
			if (ctrl) 
				return { true, m_currentDevice, KeyCode::ctrl_q };
			break;
		case ' ':
			return { true, m_currentDevice, KeyCode::spacebar };

		default:
			// for the moment we stricly control events propagated 
			//std::cout << "default : key : " << rawEvent.code << "\n";
			return UNVALID_EVENT;
		}

		return UNVALID_EVENT;
	}
}
