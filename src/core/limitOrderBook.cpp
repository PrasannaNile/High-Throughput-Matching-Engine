#include "core/limitOrderBook.h"

namespace MatchingEngine {
    void LimitOrderBook::addOrder(const Order& order) {
        if (order.orderSide == OrderSideEnum::BUY) {
            PriceLevel& shelf = bids[order.orderPrice];
            shelf.pushOrder(order);
            orderRegistry[order.orderId] = std::prev(shelf.orderQueue.end());
        } else {
            PriceLevel& shelf = asks[order.orderPrice];
            shelf.pushOrder(order);
            orderRegistry[order.orderId] = std::prev(shelf.orderQueue.end());
        }
    }

    bool LimitOrderBook::cancelOrder(uint64_t orderId) {
        auto it = orderRegistry.find(orderId);
        if (it == orderRegistry.end()) return false;
        
        std::list<Order>::iterator orderIt = it->second;
        uint64_t price = orderIt->orderPrice;
        OrderSideEnum side = orderIt->orderSide;
        
        if (side == OrderSideEnum::BUY) {
            PriceLevel& shelf = bids[price];
            
            // 1. Use the clean utility method we built!
            shelf.eraseOrder(orderIt); 
            
            // 2. Erase the shelf from the map if it's empty
            if (shelf.orderQueue.empty()) {
                bids.erase(price);
            }
        } else {
            PriceLevel& shelf = asks[price];
            
            // 1. Use the clean utility method we built!
            shelf.eraseOrder(orderIt);
            
            // 2. Erase the shelf from the map if it's empty
            if (shelf.orderQueue.empty()) {
                asks.erase(price);
            }
        }
        
        orderRegistry.erase(it);
        return true;
    }
}
