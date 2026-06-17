#pragma once // project from multiple inclusion error

#include <cstdint>
#include <chrono>

namespace MatchingEngine {
    enum class OrderSideEnum {BUY = 1, SELL = 2};
    enum class OrderStateEnum {NEW = 1, PARTIAL_FILL = 2, MATCH = 3, CANCEL = 4, REJECT = 5};

    struct Order {
        uint64_t orderId{};
        uint64_t traderId{};
        OrderSideEnum orderSide{};
        OrderStateEnum orderState{OrderStateEnum::NEW};
        uint32_t orderQuantity{};
        uint64_t orderPrice{};
        uint64_t orderTimestamp;
        
        Order() = default;
    };
}