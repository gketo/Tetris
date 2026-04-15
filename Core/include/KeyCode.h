#pragma once

#include <string>
#include <string_view>

namespace Core {

    enum class KeyCode
	{
		None,
		// keyboard
		ENTER,
		ESCAPE,
		CHAR,
		SPACEBAR,
		ARROW_UP,
		ARROW_DOWN,
		ARROW_RIGHT,
		ARROW_LEFT,
		END_KEY,
		HOME_KEY,
		DEL_KEY,
		PAGE_UP,
		PAGE_DOWN
		//
	};

	enum class KeyModifier
    {
        None  = 0,
        Ctrl  = 1 << 0,
        // Shift = 1 << 1,
        // Alt   = 1 << 2
    };

    // Helper function to convert KeyCode enum to string
	inline std::string_view keycode_to_string(KeyCode keyCode)
	{
		switch (keyCode)
		{
		case KeyCode::ENTER: return "ENTER";
		case KeyCode::ESCAPE: return "ESCAPE";
		case KeyCode::CHAR: return "CHAR";
		case KeyCode::SPACEBAR: return "SPACEBAR";
		case KeyCode::ARROW_UP: return "ARROW_UP";
		case KeyCode::ARROW_DOWN: return "ARROW_DOWN";
		case KeyCode::ARROW_RIGHT: return "ARROW_RIGHT";
		case KeyCode::ARROW_LEFT: return "ARROW_LEFT";
		case KeyCode::END_KEY: return "END_KEY";
		case KeyCode::HOME_KEY: return "HOME_KEY";
		case KeyCode::DEL_KEY: return "DEL_KEY";
		case KeyCode::PAGE_UP: return "PAGE_UP";
		case KeyCode::PAGE_DOWN: return "PAGE_DOWN";
		case KeyCode::None: return "None";
		}
	}

	// Helper function to convert KeyModifier enum to string
	inline KeyModifier operator&(KeyModifier a, KeyModifier b)
	{
		return static_cast<KeyModifier>(
			static_cast<int>(a) & static_cast<int>(b));
	}

	inline KeyModifier operator|(KeyModifier a, KeyModifier b)
	{
		return static_cast<KeyModifier>(
			static_cast<int>(a) | static_cast<int>(b));
	}

	inline KeyModifier& operator&=(KeyModifier& a, KeyModifier b)
	{
		a = static_cast<KeyModifier>(
			static_cast<int>(a) & static_cast<int>(b));
		return a;
	}

	inline KeyModifier& operator|=(KeyModifier& a, KeyModifier b)
	{
		a = static_cast<KeyModifier>(
			static_cast<int>(a) | static_cast<int>(b));
		return a;
	}

	inline std::string keymodifier_to_string(KeyModifier modifiers)
	{
		if (modifiers == KeyModifier::None)
		{
			return "None";			
		}

		std::string result;

		auto append = [&](std::string_view name)
		{
			if (!result.empty())
				result += " | ";
			result += name;
		};

		if ((modifiers & KeyModifier::Ctrl)  == KeyModifier::Ctrl)  append("Ctrl");
		// if ((modifiers & KeyModifier::Shift) == KeyModifier::Shift) append("Shift");
		// if ((modifiers & KeyModifier::Alt)   == KeyModifier::Alt)   append("Alt");

		return result;
	}

}