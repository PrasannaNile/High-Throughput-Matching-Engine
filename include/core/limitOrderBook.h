#pragma once

#include "core/priceLevel.h"

#include <map>
#include <unordered_map>



namespace MatchingEngine {
    class LimitOrderBook {
    private:
        // 1. Buy Bookcase: Sorted Highest Price -> Lowest Price
        std::map<uint64_t, PriceLevel, std::greater<int>> bids; 
        // 1. Sell Bookcase: Sorted Lowest Price -> Highest Price
        std::map<uint64_t, PriceLevel, std::less<int>> asks; 
        // Fast address book: get exact mode of order in list
        std::unordered_map<uint64_t, std::list<Order>::iterator> orderRegistry;

        void addOrder(const Order& order); // add the new incoming order in bids or in asks

        bool cancelOrder(uint64_t orderId); // order is cancel or match, then remove it

        void matchOrder(Order& incomingOrder);

    public:
    };
}