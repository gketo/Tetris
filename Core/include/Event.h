#pragma once

#include "EventLayer.h"
#include "CommandVariant.h"
#include "Logger.h"
#include "Timestamp.h"

#include <format>
#include <string>

namespace Core {

    struct Event 
    {
        EventLayer layer;
        CommandVariant commandVar;
        Timestamp timestamp;

        Event() = default;

        Event(EventLayer layer, CommandVariant cmdVar, Timestamp ts = Timestamp::invalid())
        : layer{ layer }
        , commandVar{ cmdVar }
        , timestamp{ ts }
        {
            // if (!timestamp.is_valid())
            // {
            //     LOG_ERROR("[Event] Timestamp invalid. Setting layer to low");
            //     layer = EventLayer::VeryLow;
            // }
        }

        bool operator==(const Event& other) const = default;

        std::string to_string() const
        {
            return std::format("[Event] -> Timestamp ms: {}, Layer: {}, CommandVar: {}"
                , timestamp.to_ms()
                , dbg_to_string(layer)
                , dbg_to_string(commandVar)
            );
        }
    };

}