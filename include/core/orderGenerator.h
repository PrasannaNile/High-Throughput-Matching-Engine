#pragma once

#include "./order.h"

#include <vector>
#include <cstdint>
#include <random>


namespace MatchingEngine {
    class OrderGenerator {
    private:
        std::vector<MatchingEngine::Order> orderPool;
        int minPrice;
        int maxPrice;
        int minQty;
        int maxQty;
        std::mt19937 randEngine;
        std::uniform_int_distribution<uint32_t> distQty;
        std::uniform_int_distribution<uint64_t> distPrice;


    public:
        OrderGenerator() {};

        void generateOrder(const uint32_t orderCount);
    };
}