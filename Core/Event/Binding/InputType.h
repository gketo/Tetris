#pragma once

// ==================== Includes ====================
#include <string>
#include <string_view>

namespace Core {

    enum class InputType
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

	enum class InputModifier
    {
        None  = 0,
        Ctrl  = 1 << 0,
        // Shift = 1 << 1,
        // Alt   = 1 << 2
    };

    // Helper function to convert InputType to string
	inline std::string_view dbg_to_string(InputType inputType)
	{
		switch (inputType)
		{
		case InputType::ENTER:          return "ENTER";
		case InputType::ESCAPE:         return "ESCAPE";
		case InputType::CHAR:           return "CHAR";
		case InputType::SPACEBAR:       return "SPACEBAR";
		case InputType::ARROW_UP:       return "ARROW_UP";
		case InputType::ARROW_DOWN:     return "ARROW_DOWN";
		case InputType::ARROW_RIGHT:    return "ARROW_RIGHT";
		case InputType::ARROW_LEFT:     return "ARROW_LEFT";
		case InputType::END_KEY:        return "END_KEY";
		case InputType::HOME_KEY:       return "HOME_KEY";
		case InputType::DEL_KEY:        return "DEL_KEY";
		case InputType::PAGE_UP:        return "PAGE_UP";
		case InputType::PAGE_DOWN:      return "PAGE_DOWN";
		case InputType::None:           return "None";
		}
        return "Unknown";
	}

	// Helper function to convert InputModifier enum to string
	inline InputModifier operator&(InputModifier a, InputModifier b)
	{
		return static_cast<InputModifier>(
			static_cast<int>(a) & static_cast<int>(b));
	}

	inline InputModifier operator|(InputModifier a, InputModifier b)
	{
		return static_cast<InputModifier>(
			static_cast<int>(a) | static_cast<int>(b));
	}

	inline InputModifier& operator&=(InputModifier& a, InputModifier b)
	{
		a = static_cast<InputModifier>(
			static_cast<int>(a) & static_cast<int>(b));
		return a;
	}

	inline InputModifier& operator|=(InputModifier& a, InputModifier b)
	{
		a = static_cast<InputModifier>(
			static_cast<int>(a) | static_cast<int>(b));
		return a;
	}

	inline std::string dbg_to_string(InputModifier modifiers)
	{
		if (modifiers == InputModifier::None)
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

		if ((modifiers & InputModifier::Ctrl)  == InputModifier::Ctrl)  append("Ctrl");
		// if ((modifiers & InputModifier::Shift) == InputModifier::Shift) append("Shift");
		// if ((modifiers & InputModifier::Alt)   == InputModifier::Alt)   append("Alt");

		return result;
	}

}