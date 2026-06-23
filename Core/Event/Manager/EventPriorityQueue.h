#pragma once

#include "Core/Event/Events/Event.h"

#include <queue>

namespace Core {
// todo implement 3 queues with weights to prevent starvation (flooding by higher layer events)
// 2. Multiple queues (very common)
//     Have separate FIFO queues per layer level:
//     std::queue<Event> high;
//     std::queue<Event> medium;
//     std::queue<Event> low;
//     Processing loop:
//     Try high
//     Then medium
//     Then low
//     Optionally: add fairness (e.g., process 5 high, then 1 low).
    struct compare 
    {
        bool operator()(const Event& a, const Event& b) const
        {
            // Lower layer loses
            if (a.layer == b.layer)
            {
                return a.timestamp > b.timestamp;
            }

            // Newer event loses (FIFO for equal layer)
            return a.layer < b.layer;
        }
    };

    using EventPriorityQueue = std::priority_queue<Event, std::vector<Event>, compare>;
}