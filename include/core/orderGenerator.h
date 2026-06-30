#pragma once

#include "./order.h"

#include <vector>
#include <cstdint>
#include <random>


namespace MatchingEngine {
    class OrderGenerator {
    private:
        std::vector<MatchingEngine::Order> orderPool;
        uint64_t minPrice;
        uint64_t maxPrice;
        uint32_t minQty;
        uint32_t maxQty;
        std::mt19937 randEngine;
        std::uniform_int_distribution<uint32_t> distQty;
        std::uniform_int_distribution<uint64_t> distPrice;


    public:
        OrderGenerator();

        void generateOrder(const uint32_t orderCount);
        std::vector<MatchingEngine::Order>& getOrderPool();
    };
}