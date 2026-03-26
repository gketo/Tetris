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
        em.bindKey(KeyCode::spacebar, EngineAction::PLAY);
        em.bindKey(KeyCode::key_R, EngineAction::RESUME);
        em.bindKey(KeyCode::key_P, EngineAction::PAUSE);
        em.bindKey(KeyCode::key_Q, EngineAction::QUIT);
    }

	std::optional<KeyCode> CtrlKeyboard::readEvent() const
	{
        auto event = m_eventSource.readEvent();
	
		if (!event)
		{
			return std::nullopt; // propagate
		}
        
        //LOG_DEBUG("[CtrlKeyboard] readEvent: %s", event->to_string().c_str());
        
        if (event->key == ' ')
        {
            return KeyCode::spacebar;
        }

        if (event->isCtrl)
        {
            switch (event->key)     // interpret as ASCII int 
            { 
            case 'P':   return KeyCode::ctrl_P;
            case 'Q':   return KeyCode::ctrl_Q;
            }
        }

        switch (event->key)     // interpret as ASCII int 
        { 
        case 'p':   return KeyCode::key_P;
        case 'q':   return KeyCode::key_Q;
        case 'r':   return KeyCode::key_R;
        }

        // treat any other event as unregistred
		LOG_DEBUG("[CtrlKeyboard] Unregistered event ");
        return std::nullopt;
	}
}