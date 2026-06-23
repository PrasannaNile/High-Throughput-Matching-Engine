#include "core/limitOrderBook.h"


#include <iostream>

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

    void LimitOrderBook::processOrder(Order& incomingOrder) {

        matchOrder(incomingOrder);

        if(incomingOrder.orderQuantity > 0) addOrder(incomingOrder);
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
                        if(shelf.orderQueue.empty()) asks.erase(asks.begin());
                    }
                    break;
                } else {
                    incomingOrder.orderQuantity -= restingOrder.orderQuantity;
                    orderRegistry.erase(restingOrder.orderId);
                    shelf.orderQueue.erase(shelf.orderQueue.begin());
                    if(shelf.orderQueue.empty()) asks.erase(asks.begin());
                }
            }

        } else {

            while(bids.begin() != bids.end() && incomingOrder.orderPrice <= bids.begin()->first) {
                PriceLevel& shelf = asks.begin()->second;
                Order& restingOrder = shelf.orderQueue.front();
                
                uint64_t matchQty = std::min(incomingOrder.orderQuantity, restingOrder.orderQuantity);

                if(incomingOrder.orderQuantity <= restingOrder.orderQuantity) {
                    restingOrder.orderQuantity -= matchQty;
                    shelf.totalVolume -= matchQty;
                    incomingOrder.orderQuantity = 0;

                    if(restingOrder.orderQuantity == 0) {
                        orderRegistry.erase(restingOrder.orderId);
                        shelf.orderQueue.erase(shelf.orderQueue.begin());
                        if(shelf.orderQueue.empty()) bids.erase(bids.begin());

                    }
                    break;
                } else {
                    incomingOrder.orderQuantity -= restingOrder.orderQuantity;
                    orderRegistry.erase(restingOrder.orderId);
                    shelf.orderQueue.erase(shelf.orderQueue.begin());

                    if(shelf.orderQueue.empty()) bids.erase(bids.begin());
                }

            }

        }
    }

    void LimitOrderBook::displayBuyers() {
        if(bids.empty()) std::cerr << "[Book Error] xxxxxxxx No Buyers Order yet xxxxxxxxx";

        else {
            std::cout << "*************** Buyers (bids) ***************** " << "\n";
            for(const auto& [price, shelf]: bids) {
                std::cout << "Price: " << price << " | TotalVol: " << shelf.totalVolume << " => ";
                for(const auto& restingOrder: shelf.orderQueue) {
                    std::cout << "[ OrderId: " << restingOrder.orderId << ", Quantity: " << restingOrder.orderQuantity << " ]"; 
                }
            }
        }
        std::cout << "\n\n";
    }

    void LimitOrderBook::displaySellers() {
        if(asks.empty()) std::cerr << "[Book Error] xxxxxxxx No Sellers Order yet xxxxxxxxx";

        else {
            std::cout << "*************** Sellers (asks) ***************** " << "\n";
            for(const auto& [price, shelf]: asks) {
                std::cout << "Price: " << price << " | TotalVol: " << shelf.totalVolume << " => ";
                for(const auto& restingOrder: shelf.orderQueue) {
                    std::cout << "[ OrderId: " << restingOrder.orderId << ", Quantity: " << restingOrder.orderQuantity << " ] "; 
                }
            }
        }
        std::cout << "\n\n";
    }


}
