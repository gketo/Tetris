#pragma once

// ==================== Includes ====================
#include <limits>
#include <string_view>

namespace Core {

    enum class EventLayer
    {
        Desactivated    = 0,
        VeryLow         = 1,
        GameCtrl        = 100,
        GameMenu        = 200,
        EngineRunning   = 300,
        Menu            = 400,
        System          = std::numeric_limits<int>::max(),
    };

    // Helper function to convert EventLayer to string
	inline std::string_view dbg_to_string(EventLayer layer)
	{
		switch (layer)
		{
		case EventLayer::Desactivated:  return "Desactivated";
		case EventLayer::VeryLow:       return "VeryLow";
		case EventLayer::GameCtrl:      return "GameCtrl";
		case EventLayer::GameMenu:      return "GameMenu";
		case EventLayer::EngineRunning: return "EngineRunning";
		case EventLayer::Menu:          return "Menu";
		case EventLayer::System:        return "System";
		}
        return "Unknown";
	}
}