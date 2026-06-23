#include "core/PriceLevel.h"

namespace MatchingEngine {

    void PriceLevel::pushOrder(const Order& order) {
        orderQueue.push_back(order);
        totalVolume += order.orderQuantity;
        orderCount++;
    }

    std::list<Order>::iterator PriceLevel::eraseOrder(std::list<Order>::iterator it) {
        totalVolume -= it->orderQuantity;
        orderCount--;
        return orderQueue.erase(it);
    }

} // namespace MatchingEngine