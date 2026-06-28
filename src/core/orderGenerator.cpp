#include "core/orderGenerator.h"



namespace MatchingEngine {
    OrderGenerator::OrderGenerator() : minPrice{90}, maxPrice{110}, minQty{1}, 
        maxQty{100}, randEngine{std::random_device{}()}, distQty{minQty, maxQty}, distPrice{minPrice, maxPrice} {

    }
    
    void OrderGenerator::generateOrder(const uint32_t orderCount) {
    }
}