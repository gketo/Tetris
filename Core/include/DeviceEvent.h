#pragma once

#include "DeviceType.h"
#include "KeyCode.h"
#include "SourceType.h"

#include <format>
#include <optional>
#include <string>

namespace Core {

    struct DeviceEvent
    {
        DeviceEvent() = default;

        DeviceEvent(SourceType source, DeviceType device, KeyCode code, std::optional<char> ch = std::nullopt, KeyModifier modifiers = KeyModifier::None)
        : source{ source }
        , device{ device }
        , code{ code }
        , ch{ ch }
        , modifiers{ modifiers }
        {}

        SourceType source{ SourceType::None };
        DeviceType device{ DeviceType::None };
        KeyCode code{ KeyCode::None };
        std::optional<char> ch;
        KeyModifier modifiers{ KeyModifier::None };

        bool operator==(const DeviceEvent&) const = default;
        // bool operator==(const DeviceEvent& other) const
        // {
        //     return  source      == other.source  &&
        //             device      == other.device  &&
        //             code        == other.code    &&
        //             ch          == other.ch      &&
        //             modifiers   == other.modifiers;
        // }

        std::string to_string() const
        {
            return std::format("[DeviceEvent] -> Source: {}, Device: {}, KeyCode: {}, KeyModifiers: {}, ch (opt): {}", source_to_string(source), device_to_string(device), keycode_to_string(code), keymodifier_to_string(modifiers), (ch ? std::string{1, *ch} : "None"));
        }
    };
	
}