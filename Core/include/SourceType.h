#pragma once

#include <string_view>

namespace Core {

    enum class SourceType
    {
        None,
        TERMINAL
    };

    // Helper function to convert SourceType enum to string
	inline std::string_view source_to_string(SourceType source)
	{
		switch (source)
		{
		case SourceType::None: return "None";
		case SourceType::TERMINAL: return "TERMINAL";
		}
	}

}