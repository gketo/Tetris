#include "CtrlInterface.h"

namespace Core {

	class CtrlKeyboard : public CtrlInterface {
	public:
		CtrlKeyboard(DeviceType device)
			: CtrlInterface{ device }
		{ }

		InputEvent interpretTerminalRead(WORD read) override
		{
			switch (read)
			{
			case 27:
				return { m_currentDevice, InputCode::escape };
			default:
				return { DeviceType::None, InputCode::None };
			}
		}
	};
}
