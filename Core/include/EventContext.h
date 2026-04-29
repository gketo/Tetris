#pragma once

#include "EventLayer.h"

#include <unordered_set>

namespace Core {

    class EventContext
    {
    public:
        void pushLayer(EventLayer layer)
        {
            activeLayers.insert(layer);
        }

        void removeLayer(EventLayer layer)
        {
            activeLayers.erase(layer);
        }

        bool isActive(EventLayer layer) const
        {
            return activeLayers.contains(layer);
        }

    private:
        std::unordered_set<EventLayer> activeLayers;
    };
}