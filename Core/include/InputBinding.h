#pragma once

#include "CommandVariant.h"
#include "DeviceEvent.h"
#include "DeviceType.h"
#include "Event.h"
#include "EventLayer.h"
#include "InputType.h"
#include "SourceType.h"

#include <optional>
#include <string>

namespace Core {

    struct InputBinding 
    {
        InputBinding(EventLayer layer, CommandVariant commandVar, SourceType source, DeviceType device, InputType input, std::optional<char> ch = std::nullopt, InputModifier modifiers = InputModifier::None)
        : layer{ layer }
        , commandVar{ commandVar } 
        , source{ source }
        , device{ device }
        , input{ input }
        , ch{ ch }
        , modifiers{ modifiers }
        {}

        // app event
        EventLayer layer;
        CommandVariant commandVar;

        // device event
        SourceType source{ SourceType::None };
        DeviceType device{ DeviceType::None };
        InputType input{ InputType::None };
        std::optional<char> ch;
        InputModifier modifiers{ InputModifier::None };

        bool operator==(const InputBinding& other) const = default;

        bool weakCompare(const Event& other) const
        {
            return layer == other.layer &&
                commandVar == other.commandVar;
        }

        bool weakCompare(const DeviceEvent& other) const
        {
            return source == other.source &&
                device == other.device &&
                input == other.input &&
                ch == other.ch &&
                modifiers == other.modifiers;
        }

        inline std::string to_string() const
        {
            return std::format("[InputBinding] -> Layer: {}, CommandVar: {}, Source: {}, Device: {}, InputType: {}, KeyModifiers: {}, ch (opt): {}"
                , dbg_to_string(layer)
                , dbg_to_string(commandVar)
                , dbg_to_string(source)
                , dbg_to_string(device)
                , dbg_to_string(input)
                , dbg_to_string(modifiers)
                , (ch ? std::string{1, *ch} : "None")
            );
        }
    };

}