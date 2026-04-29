#pragma once

#include "CommandVariant.h"
#include "DeviceEvent.h"
#include "Event.h"
#include "Timestamp.h"

// to_string
#include "EngineCommand.h"
#include "EventLayer.h"
#include "MenuCommand.h"
#include "TetrisCommand.h"

namespace Core {

    struct InputBinding 
    {
        InputBinding(EventLayer layer, CommandVariant commandVar, SourceType source, DeviceType device, KeyCode code, std::optional<char> ch = std::nullopt, KeyModifier modifiers = KeyModifier::None)
        : layer{ layer }
        , commandVar{ commandVar } 
        , source{ source }
        , device{ device }
        , code{ code }
        , ch{ ch }
        , modifiers{ modifiers }
        {}

        // app event
        EventLayer layer;
        CommandVariant commandVar;

        // device event
        SourceType source{ SourceType::None };
        DeviceType device{ DeviceType::None };
        KeyCode code{ KeyCode::None };
        std::optional<char> ch;
        KeyModifier modifiers{ KeyModifier::None };

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
                code == other.code &&
                ch == other.ch &&
                modifiers == other.modifiers;
        }

        inline std::string to_string() const
        {
            return std::format("[InputBinding] -> Layer: {}, CommandVar: {}, Source: {}, Device: {}, KeyCode: {}, KeyModifiers: {}, ch (opt): {}"
                , dbg_to_string(layer)
                , dbg_to_string(commandVar)
                , source_to_string(source)
                , device_to_string(device)
                , keycode_to_string(code)
                , keymodifier_to_string(modifiers)
                , (ch ? std::string{1, *ch} : "None")
            );
        }
    };

}