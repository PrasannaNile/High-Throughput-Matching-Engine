#pragma once

#include <cstdint>
#include <chrono>

namespace MatchingEngine {

    struct Trade {
        uint64_t tradeId{};
        uint64_t buyOrderId{};
        uint64_t sellOrderId{};
        uint64_t matchPrice{};
        uint64_t tradeTimestamp{};
        uint32_t matchQuantity{}; // move to last because of extra padding require of 4 bytes

        Trade() = default;
    };
}