#include "CtrlKeyboard.h"

#include "ActionVariant.h"
#include "DeviceEvent.h"
#include "EngineAction.h"
#include "EventManager.h"
#include "KeyCode.h"
#include "Logger.h"

#include <optional>

namespace Core {
	std::optional<DeviceEvent> CtrlKeyboard::readEvent() const
	{
        return m_eventSource.readEvent();
	}
}



	// void CtrlKeyboard::bind(EventManager& em) const
    // {
	// 	LOG_DEBUG("[CtrlKeyboard] Binding keys...");
    //     em.bindKey( Core::KeyCode::ENTER, Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::SELECT });
    //     em.bindKey( Core::KeyCode::SPACEBAR, Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::PLAY });
    //     em.bindKey( Core::KeyCode::KEY_R, Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::RESUME });
    //     em.bindKey( Core::KeyCode::KEY_P, Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::PAUSE });
    //     em.bindKey( Core::KeyCode::KEY_Q, Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::QUIT });
    //     em.bindKey( Core::KeyCode::ARROW_UP, Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::MOVE_UP });
    //     em.bindKey( Core::KeyCode::ARROW_DOWN, Core::ActionVariant{ std::in_place_type<EngineAction>, EngineAction::MOVE_DOWN });
    // }
