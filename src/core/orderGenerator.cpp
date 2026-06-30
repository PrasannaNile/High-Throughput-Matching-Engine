#include "core/orderGenerator.h"



namespace MatchingEngine {
    OrderGenerator::OrderGenerator() : 
        minPrice{90}, 
        maxPrice{110}, 
        minQty{1}, 
        maxQty{100}, 
        randEngine{std::random_device{}()}, 
        distQty{minQty, maxQty}, 
        distPrice{minPrice, maxPrice} 
    {}
    
    void OrderGenerator::generateOrder(const uint32_t orderCount) {
        this->orderPool.clear();
        this->orderPool.reserve(orderCount);

        for(int i = 1; i <= orderCount; i++) {
            Order incomingOrder {i, i, (i%2 == 0) ? OrderSideEnum::BUY : OrderSideEnum::SELL, 
                                 OrderStateEnum::NEW, this->distQty(this->randEngine), this->distPrice(this->randEngine)};

            orderPool.push_back(incomingOrder);
        }
    }

    std::vector<Order>& OrderGenerator::getOrderPool()  {
        return this->orderPool;
    }
} 