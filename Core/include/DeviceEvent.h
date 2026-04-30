#pragma once

#include "DeviceType.h"
#include "InputType.h"
#include "SourceType.h"
#include "Timestamp.h"

#include <format>
#include <optional>
#include <string>

namespace Core {

    struct DeviceEvent
    {
        DeviceEvent() = default;

        DeviceEvent(SourceType source, DeviceType device, InputType input, std::optional<char> ch = std::nullopt, InputModifier modifiers = InputModifier::None)
        : source{ source }
        , device{ device }
        , input{ input }
        , ch{ ch }
        , modifiers{ modifiers }
        , timestamp {} // automatic
        {}

        SourceType source{ SourceType::None };
        DeviceType device{ DeviceType::None };
        InputType input{ InputType::None };
        std::optional<char> ch;
        InputModifier modifiers{ InputModifier::None };
        Timestamp timestamp;

        bool operator==(const DeviceEvent& other) const
        {
            return timestamp.value == other.timestamp.value &&
                source == other.source &&
                device == other.device &&
                input == other.input &&
                ch == other.ch &&
                modifiers == other.modifiers;
        }

        std::string to_string() const
        {
            return std::format("[DeviceEvent] -> Timestamp: {}, Source: {}, Device: {}, InputType: {}, KeyModifiers: {}, ch (opt): {}"
                , timestamp.to_ms()
                , dbg_to_string(source)
                , dbg_to_string(device)
                , dbg_to_string(input)
                , dbg_to_string(modifiers)
                , (ch ? std::string{1, *ch} : "None")
            );
        }
    };
	
}