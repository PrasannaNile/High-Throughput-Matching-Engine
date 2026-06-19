#include "core/limitOrderBook.h"

namespace MatchingEngine {
    void LimitOrderBook::addOrder(const Order& order) {
        if(order.orderSide == OrderSideEnum::BUY) {
            // find or create the shelf
            PriceLevel shelf = bids[order.orderPrice];
            // worker shelf will add the order card
            shelf.addOrder(order);
            // Register the smart pointer in our global address book
            orderRegistry[order.orderId] = std::prev(shelf.orderQueue.end());
        } else {
            // find or create the shelf
            PriceLevel shelf = asks[order.orderPrice];

            shelf.addOrder(order);

            orderRegistry[order.orderId] = std::prev(shelf.orderQueue.end());
        }
    }
}
