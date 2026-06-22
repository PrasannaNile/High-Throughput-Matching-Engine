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
        auto it = orderRegistry.find(orderId); // find order in address book 
        if (it == orderRegistry.end()) return false; // if order not exist return false
        
        std::list<Order>::iterator orderIt = it->second; // order exist then get node pointer(smart pointer)
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

    void LimitOrderBook::matchOrder(Order& incomingOrder) {
        // type of order and look in to opposite orders map
        if(incomingOrder.orderSide == OrderSideEnum::BUY) {
            // if atleast one seller exist and buyer can afford the price
            while(asks.begin() != asks.end() && incomingOrder.orderPrice >= asks.begin()->first) {
                PriceLevel& shelf = asks.begin()->second; // get the shelf of all orders with incoming price 
                Order& restingOrder = shelf.orderQueue.front(); // get first order from shelf
                // get the min quantity for trade to be valid 
                uint64_t matchQty = std::min(incomingOrder.orderQuantity, restingOrder.orderQuantity);
                // incoming order will get completely exhaust
                if(incomingOrder.orderQuantity <= restingOrder.orderQuantity) {
                    restingOrder.orderQuantity -= matchQty; // substract from resting order of seller
                    shelf.totalVolume -= matchQty;
                    incomingOrder.orderQuantity = 0;

                    if(restingOrder.orderQuantity == 0) { // resting order also gets exhaust
                        orderRegistry.erase(restingOrder.orderId);
                        shelf.eraseOrder(shelf.orderQueue.begin());
                    }
                }
            }

        } else {

            while(bids.begin() != bids.end() && incomingOrder.orderPrice <= bids.begin()->first) {

                

            }

        }
    }

}
