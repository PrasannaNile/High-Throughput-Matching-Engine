#pragma once

#include "core/order.h"

#include <cstdint>
#include <list>

namespace MatchingEngine {
    struct PriceLevel {
        // --- State member (cached aligned) ---
        uint64_t price;
        uint64_t totalVolume;
        uint32_t orderCount;
        // --- Time Priority for Orders ---
        std::list<Order> orderQueue;
        // --- Interface Blueprint (Core Actions) ---
        PriceLevel() = default;
        explicit PriceLevel(uint64_t levelPrice);

        // Adds an order to the back of the queue (O(1))
        void pushOrder(const Order& order);

        std::list<Order>::iterator eraseOrder(std::list<Order>::iterator it);

        // Consumes volume from the front order during a match (O(1))
        void executeMatch(uint32_t matchQuantity);
    };
}