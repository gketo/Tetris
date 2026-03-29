#include "CtrlKeyboard.h"

#include "Action.h"
#include "DeviceEvent.h"
#include "EventManager.h"
#include "Logger.h"

#include <optional>

namespace Core {

	void CtrlKeyboard::bind(EventManager& em) const
    {
		LOG_DEBUG("[CtrlKeyboard] Binding keys...");
        em.bindKey(KeyCode::SPACEBAR, EngineAction::PLAY);
        em.bindKey(KeyCode::KEY_R, EngineAction::RESUME);
        em.bindKey(KeyCode::KEY_P, EngineAction::PAUSE);
        em.bindKey(KeyCode::KEY_Q, EngineAction::QUIT);
    }

	std::optional<KeyCode> CtrlKeyboard::readEvent() const
	{
        auto eventOpt = m_eventSource.readEvent();
	
		if (!eventOpt)
		{
			return std::nullopt; // propagate
		}
        
        auto event = *eventOpt;
        //LOG_DEBUG("[CtrlKeyboard] readEvent: %s", event->to_string().c_str());
        
        if (event.key == ' ')
        {
            return KeyCode::SPACEBAR;
        }

        if (event.isCtrl)
        {
            switch (event.key)     // interpret as ASCII int 
            { 
            case 'P':   return KeyCode::CTRL_P;
            case 'Q':   return KeyCode::CTRL_Q;
            }
        }

        switch (event.key)     // interpret as ASCII int 
        { 
        case 'p':   return KeyCode::KEY_P;
        case 'q':   return KeyCode::KEY_Q;
        case 'r':   return KeyCode::KEY_R;
        }

        // treat any other event as unregistred
		LOG_DEBUG("[CtrlKeyboard] Unregistered event ");
        return std::nullopt;
	}
}